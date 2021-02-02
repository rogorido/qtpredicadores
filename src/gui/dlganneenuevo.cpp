#include "dlganneenuevo.h"

#include <QCompleter>
#include <QDebug>
#include <QKeyEvent>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableWidget>

#include "dlgseleccionargeneral.h"
#include "src/widgets/myqmdiarea.h"
#include "ui_dlganneenuevo.h"

const QString sql_autores =
    "SELECT DISTINCT author_initial_text FROM annee_general ORDER BY "
    "author_initial_text";
const QString sql_temas =
    "SELECT DISTINCT main_theme FROM annee_general ORDER BY main_theme";
const QString sql_conceptos =
    "SELECT DISTINCT unnest(concepts) AS conceptos FROM meditations ORDER BY "
    "conceptos";

dlgAnneeNuevo::dlgAnneeNuevo(QWidget *parent)
    : QWidget(parent), ui(new Ui::dlgAnneeNuevo)
{
  ui->setupUi(this);
  mdiarea = MyQmdiArea::Instance(this);

  ui->txtPalabraMeditacion->installEventFilter(this);

  connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(cerrar()));
  connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarAnnee()));
  connect(ui->btAnadirPersonaPrincipal, SIGNAL(clicked(bool)), this,
          SLOT(anadirPersona()));
  connect(ui->btAnadirPersonaAdicional, SIGNAL(clicked(bool)), this,
          SLOT(anadirPersonaAdicional()));
  connect(ui->btQuitarPersonaAdicional, SIGNAL(clicked(bool)), this,
          SLOT(quitarPersonaAdicional()));
  connect(ui->btAnadirMeditacion, SIGNAL(clicked(bool)), this,
          SLOT(anadirMeditacion()));
  connect(ui->btQuitarMeditacion, SIGNAL(clicked(bool)), this,
          SLOT(quitarMeditacion()));
  connect(ui->btAnadirPalabraMeditacion, SIGNAL(clicked(bool)), this,
          SLOT(anadirConceptoMeditacion()));
  connect(ui->btQuitarPalabraMeditacion, SIGNAL(clicked(bool)), this,
          SLOT(quitarConceptoMeditacion()));
  connect(ui->btAnadirCategoriaGeneral, SIGNAL(clicked(bool)), this,
          SLOT(anadirCategoriasGeneral()));
  connect(ui->btQuitarCategoriaGeneral, SIGNAL(clicked(bool)), this,
          SLOT(quitarCategoriasGeneral()));
  connect(ui->btTemas, SIGNAL(clicked(bool)), this,
          SLOT(anadirCategoriasMeditacion()));

  ui->twMeditaciones->setColumnCount(3);
  ui->twPersonasAdicionales->setColumnCount(1);
  ui->lblPersonaPrincipal->setText("");

  cargarModelos();
}

dlgAnneeNuevo::~dlgAnneeNuevo() { delete ui; }

bool dlgAnneeNuevo::eventFilter(QObject *obj, QEvent *e)
{
  if (e->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
    if (keyEvent->key() == Qt::Key_Return) {
      // y ahora dependiendo del QLineEdit...
      if (obj == ui->txtPalabraMeditacion) {
        anadirConceptoMeditacion();
        return true;
      }
    }
  }

  /*
   * atención aquí lo importante es poner QWidget!
   * si pongo dlgPenaEntrada no funciona!!
   */
  return QWidget::eventFilter(obj, e);
}

void dlgAnneeNuevo::cerrar() { parentWidget()->close(); }

void dlgAnneeNuevo::aceptarAnnee()
{
  if (persona_id == 0) {
    int ret = QMessageBox::warning(this, "Error",
                                   "Hay que escoger una persona principal.");
    Q_UNUSED(ret)
    return;
  }

  QSqlQuery query;
  int dia = ui->spDia->value();
  int mes = ui->spMes->value();
  QString initial_text = ui->txtPensamiento->toPlainText();
  QString author_initial_text = ui->txtAutorPensamiento->text();
  QString entradilla = ui->txtEntradilla->toPlainText();
  QString main_theme = ui->txtTemaPrincipal->text();
  QString final_thoughts = ui->txtFinalThought->toPlainText();

  query.prepare(
      "INSERT INTO annee.annee_general(day, month, mainperson, initial_text, "
      "author_initial_text, main_theme, entradilla, final_thoughts) "
      "VALUES(:dia, :mes, :personaprincipal, :initial_text, "
      ":author_initial_text, :main_theme, :entradilla, :final_thoughts)");
  query.bindValue(":dia", dia);
  query.bindValue(":mes", mes);
  query.bindValue(":personaprincipal", persona_id);
  query.bindValue(":initial_text", initial_text);
  query.bindValue(":author_initial_text", author_initial_text);
  query.bindValue(":main_theme", main_theme);
  query.bindValue(":entradilla", entradilla);
  query.bindValue(":final_thoughts", final_thoughts);

  if (query.exec()) {
    QSqlQuery lastid("select max(day_id) from annee.annee_general");

    lastid.first();
    int id = lastid.value(0).toInt();

    meterMeditaciones(id);
    meterPersonasAdicionales(id);
    meterCategoriasGenerales(id);
    borrarCampos();
  }
  else {
    int ret = QMessageBox::warning(
        this, "Error", "Ha habido un error en la tabla annee_general.");
    Q_UNUSED(ret)
    qDebug() << query.lastError();
    return;
  }
}

void dlgAnneeNuevo::anadirPersona()
{
  dlgSeleccionarGeneral *seleccionar =
      new dlgSeleccionarGeneral(PERSONA, true, this);
  connect(seleccionar, SIGNAL(personaEscogidaSignal(Persona)), this,
          SLOT(recibirPersonaPrincipal(Persona)));

  QMdiSubWindow *window = mdiarea->addSubWindow(seleccionar);
  window->show();
}

void dlgAnneeNuevo::anadirPersonaAdicional()
{
  dlgSeleccionarGeneral *seleccionar =
      new dlgSeleccionarGeneral(PERSONA, true, this);
  connect(seleccionar, SIGNAL(personaEscogidaSignal(Persona)), this,
          SLOT(recibirPersonaAdicional(Persona)));

  QMdiSubWindow *window = mdiarea->addSubWindow(seleccionar);
  window->show();
}

void dlgAnneeNuevo::quitarPersonaAdicional()
{
  QModelIndex idx = ui->twPersonasAdicionales->currentIndex();

  if (!idx.isValid()) return;

  int row = ui->twPersonasAdicionales->currentRow();
  ui->twPersonasAdicionales->removeRow(row);

  personas_adicionales.removeAt(row);
}

void dlgAnneeNuevo::anadirMeditacion()
{
  m_meditacion meditacion;
  QString categorias_lista;  // esto es para el widgetitem

  meditacion.numeracion = ui->spNumeroMeditacion->value();
  meditacion.pensamiento = ui->txtMeditacion->text();
  meditacion.categorias = categorias_seleccionadas_meditaciones;
  meditacion.conceptos = m_conceptos;

  meditaciones.append(meditacion);

  /* añadimos un elem a la tabla: este es el mejor método? */
  QTableWidgetItem *item1 =
      new QTableWidgetItem(QString::number(meditacion.numeracion));
  QTableWidgetItem *item2 = new QTableWidgetItem(meditacion.pensamiento);

  // lo de las categorías es más complicado...
  QHashIterator<int, QString> i(categorias_seleccionadas_meditaciones);
  while (i.hasNext()) {
    i.next();
    categorias_lista = categorias_lista + i.value() + QString(", ");
  }
  QTableWidgetItem *item3 = new QTableWidgetItem(categorias_lista);

  // this will give the present number of rows available.
  int insertRow = ui->twMeditaciones->rowCount();
  // insert the row at the bottom of the table widget - using.
  ui->twMeditaciones->insertRow(insertRow);

  ui->twMeditaciones->setItem(insertRow, 0, item1);
  ui->twMeditaciones->setItem(insertRow, 1, item2);
  ui->twMeditaciones->setItem(insertRow, 2, item3);

  ui->twMeditaciones->resizeColumnsToContents();
  ui->twMeditaciones->resizeRowsToContents();

  // tenemos que borrar algunas cosas
  ui->txtMeditacion->setText("");
  categorias_seleccionadas_meditaciones.clear();
  m_conceptos.clear();
  ui->lwPalabrasMeditacion->clear();
}

void dlgAnneeNuevo::quitarMeditacion()
{
  QModelIndex idx = ui->twMeditaciones->currentIndex();

  if (!idx.isValid()) return;

  int row = ui->twMeditaciones->currentRow();
  ui->twMeditaciones->removeRow(row);

  meditaciones.removeAt(row);
}

void dlgAnneeNuevo::anadirConceptoMeditacion()
{
  if (ui->txtPalabraMeditacion->text().isEmpty()) return;

  QListWidgetItem *item = new QListWidgetItem(ui->txtPalabraMeditacion->text(),
                                              ui->lwPalabrasMeditacion);

  m_conceptos.append(ui->txtPalabraMeditacion->text());
  ui->txtPalabraMeditacion->setText("");
  ui->txtPalabraMeditacion->setFocus();
}

void dlgAnneeNuevo::quitarConceptoMeditacion()
{
  QModelIndex idx = ui->lwPalabrasMeditacion->currentIndex();

  if (!idx.isValid()) return;

  int row = ui->lwPalabrasMeditacion->currentRow();
  ui->lwPalabrasMeditacion->takeItem(ui->lwPalabrasMeditacion->currentRow());

  m_conceptos.removeAt(row);
}

void dlgAnneeNuevo::anadirCategoriasMeditacion()
{
  dlgSeleccionarGeneral *seleccionar =
      new dlgSeleccionarGeneral(TEMA, true, this);
  connect(seleccionar, SIGNAL(temaEscogidoSignal(Tema)), this,
          SLOT(recibirTemaMeditacion(Tema)));

  QMdiSubWindow *window = mdiarea->addSubWindow(seleccionar);
  window->show();
}

void dlgAnneeNuevo::anadirCategoriasGeneral()
{
  dlgSeleccionarGeneral *seleccionar =
      new dlgSeleccionarGeneral(TEMA, true, this);
  connect(seleccionar, SIGNAL(temaEscogidoSignal(Tema)), this,
          SLOT(recibirTemaGeneral(Tema)));

  QMdiSubWindow *window = mdiarea->addSubWindow(seleccionar);
  window->show();
}

void dlgAnneeNuevo::quitarCategoriasGeneral()
{
  QModelIndex idx = ui->lwCategoriasGenerales->currentIndex();

  if (!idx.isValid()) return;

  QString valor = ui->lwCategoriasGenerales->currentItem()->text();
  ui->lwCategoriasGenerales->takeItem(ui->lwCategoriasGenerales->currentRow());
  // lo de las categorías es más complicado...
  QHashIterator<int, QString> i(categorias_seleccionadas_general);
  while (i.hasNext()) {
    i.next();
    if (i.value() == valor) categorias_seleccionadas_general.remove(i.key());
  }
}

void dlgAnneeNuevo::recibirPersonaPrincipal(const Persona persona)
{
  persona_id = persona.getId();
  ui->lblPersonaPrincipal->setText(persona.getNombreCompleto());
}

void dlgAnneeNuevo::recibirPersonaAdicional(const Persona persona)
{
  otrapersona nueva_persona;

  nueva_persona.id = persona.getId();
  nueva_persona.nombre = persona.getNombreCompleto();

  personas_adicionales.append(nueva_persona);

  /* añadimos un elem a la tabla: este es el mejor método? */
  QTableWidgetItem *item = new QTableWidgetItem(nueva_persona.nombre);
  // this will give the present number of rows available.
  int insertRow = ui->twPersonasAdicionales->rowCount();
  // insert the row at the bottom of the table widget - using.
  ui->twPersonasAdicionales->insertRow(insertRow);

  ui->twPersonasAdicionales->setItem(insertRow, 0, item);

  ui->twPersonasAdicionales->resizeColumnsToContents();
  ui->twPersonasAdicionales->resizeRowsToContents();
}

void dlgAnneeNuevo::recibirTemaMeditacion(const Tema tema)
{
  categorias_seleccionadas_meditaciones.insert(tema.getId(), tema.getTema());
}

void dlgAnneeNuevo::recibirTemaGeneral(const Tema tema)
{
  categorias_seleccionadas_general.insert(tema.getId(), tema.getTema());

  QListWidgetItem *item =
      new QListWidgetItem(tema.getTema(), ui->lwCategoriasGenerales);
}

void dlgAnneeNuevo::cargarModelos()
{
  autores_model = new QSqlQueryModel(this);
  autores_model->setQuery(sql_autores);

  autores_completer = new QCompleter(this);
  autores_completer->setModel(autores_model);
  autores_completer->setCaseSensitivity(Qt::CaseInsensitive);

  ui->txtAutorPensamiento->setCompleter(autores_completer);

  temasprincipales_model = new QSqlQueryModel(this);
  temasprincipales_model->setQuery(sql_temas);

  temasprincipales_completer = new QCompleter(this);
  temasprincipales_completer->setModel(temasprincipales_model);
  temasprincipales_completer->setCaseSensitivity(Qt::CaseInsensitive);

  ui->txtTemaPrincipal->setCompleter(temasprincipales_completer);

  conceptos_model = new QSqlQueryModel(this);
  conceptos_model->setQuery(sql_conceptos);

  conceptos_completer = new QCompleter(this);
  conceptos_completer->setModel(conceptos_model);
  conceptos_completer->setCaseSensitivity(Qt::CaseInsensitive);

  ui->txtPalabraMeditacion->setCompleter(conceptos_completer);
}

void dlgAnneeNuevo::borrarCampos()
{
  ui->txtAutorPensamiento->setText("");
  ui->txtEntradilla->setText("");
  ui->txtFinalThought->setText("");
  ui->txtMeditacion->setText("");
  ui->txtPensamiento->setText("");
  ui->txtTemaPrincipal->setText("");
  ui->lblPersonaPrincipal->setText("");

  persona_id = 0;

  personas_adicionales.clear();
  meditaciones.clear();
  categorias_seleccionadas_meditaciones.clear();

  ui->twMeditaciones->clear();
  ui->twPersonasAdicionales->clear();

  ui->tabWidget->setCurrentIndex(0);

  ui->spDia->setFocus();
}

void dlgAnneeNuevo::meterMeditaciones(const int id)
{
  QSqlQuery query;
  QString conceptos_final;

  for (int i = 0; i < meditaciones.size(); ++i) {
    query.prepare(
        "INSERT INTO annee.meditations(day_id, number_meditation, "
        "text_inserted, concepts) "
        "VALUES(:dia, :number_meditation, :text_inserted, :concepts)");
    query.bindValue(":dia", id);
    query.bindValue(":number_meditation", meditaciones.at(i).numeracion);
    query.bindValue(":text_inserted", meditaciones.at(i).pensamiento);

    if (!meditaciones.at(i).conceptos.isEmpty()) {
      conceptos_final = '{' + meditaciones.at(i).conceptos.join(", ") + '}';
    }

    if (!conceptos_final.isEmpty())
      query.bindValue(":concepts", conceptos_final);
    else
      query.bindValue(":concepts", QVariant(QVariant::String));

    if (query.exec()) {
      QSqlQuery lastid("select max(meditation_id) from annee.meditations");

      lastid.first();
      int id = lastid.value(0).toInt();

      meterMeditacionesReferencias(id, i);
    }
    else {
      int ret = QMessageBox::warning(
          this, "Error", "Ha habido un error en la tabla meditations.");
      Q_UNUSED(ret)
      qDebug() << query.lastError();
      qDebug() << query.executedQuery();
      return;
    }
  }
}

void dlgAnneeNuevo::meterMeditacionesReferencias(
    const int meditation_id, const int lista_meditaciones_id)
{
  QSqlQuery query;
  QHash<int, QString> categorias =
      meditaciones.at(lista_meditaciones_id).categorias;

  // lo de las categorías es más complicado...
  QHashIterator<int, QString> i(categorias);
  while (i.hasNext()) {
    i.next();
    query.prepare(
        "INSERT INTO annee.meditations_refs(meditation_id, category_id) "
        "VALUES(:meditation_id, :category_id)");
    query.bindValue(":meditation_id", meditation_id);
    query.bindValue(":category_id", i.key());

    if (!query.exec()) {
      int ret = QMessageBox::warning(
          this, "Error",
          "Ha habido un error al ejecutar la consulta de inserción. "
          "(consulta: meterMeditacionesReferencias)");
      Q_UNUSED(ret)
      qDebug() << query.lastError();
      return;
    }
  }
}

/*
 * TODO: realmente esta tabla tiene más campos que
 * ahora aquí no estoy metiendo...
 */

void dlgAnneeNuevo::meterPersonasAdicionales(const int id)
{
  QSqlQuery query;

  for (int i = 0; i < personas_adicionales.size(); ++i) {
    query.prepare(
        "INSERT INTO annee.persons_extra(day_id, person_id) "
        "VALUES(:dia, :person_id)");
    query.bindValue(":dia", id);
    query.bindValue(":person_id", personas_adicionales.at(i).id);

    if (!query.exec()) {
      int ret = QMessageBox::warning(
          this, "Error", "Ha habido un error en la talba persons_extra.");
      Q_UNUSED(ret)
      qDebug() << query.lastError();
      return;
    }
  }
}

void dlgAnneeNuevo::meterCategoriasGenerales(const int id)
{
  QSqlQuery query;

  QHashIterator<int, QString> i(categorias_seleccionadas_general);
  while (i.hasNext()) {
    i.next();

    query.prepare(
        "INSERT INTO annee.themes_refs(day_id, category_id) "
        "VALUES(:dia, :category_id)");
    query.bindValue(":dia", id);
    query.bindValue(":category_id", i.key());

    if (!query.exec()) {
      int ret = QMessageBox::warning(
          this, "Error", "Ha habido un error en la talba themes_refs.");
      Q_UNUSED(ret)
      qDebug() << query.lastError();
      return;
    }
  }
}
