#include "dlgnuevapersona.h"

#include <QCompleter>
#include <QDebug>
#include <QJsonObject>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include "dlgdetalles.h"
#include "dlgfuenteentrada.h"
#include "src/models/personasmodel.h"
#include "src/models/qjsonmodel.h"
#include "src/objs/persona.h"
#include "src/widgets/myqmdiarea.h"
#include "ui_dlgnuevapersona.h"

dlgNuevaPersona::dlgNuevaPersona(QWidget *parent, int persona)
    : QWidget(parent), ui(new Ui::dlgNuevaPersona)
{
  ui->setupUi(this);
  cargarUI();

  if (persona != 0) {
    modificando = true;
    persona_modificando = persona;
    cargarPersona();
  }

  ui->txtNombre->setFocus();
}

dlgNuevaPersona::~dlgNuevaPersona() { delete ui; }

void dlgNuevaPersona::cargarCompleters()
{
  nombres_compl = new QCompleter(this);
  apellidos_compl = new QCompleter(this);
  diocesis_compl = new QCompleter(this);

  nombres_query = new QSqlQueryModel(this);
  apellidos_query = new QSqlQueryModel(this);
  diocesis_query = new QSqlQueryModel(this);

  nombres_query->setQuery(
      "SELECT DISTINCT name FROM persons WHERE name IS NOT NULL ORDER BY name");
  nombres_compl->setModel(nombres_query);
  nombres_compl->setCompletionColumn(0);
  nombres_compl->setCaseSensitivity(Qt::CaseInsensitive);

  ui->txtNombre->setCompleter(nombres_compl);

  apellidos_query->setQuery(
      "SELECT DISTINCT family_name FROM persons WHERE family_name IS NOT NULL "
      "ORDER BY family_name");
  apellidos_compl->setModel(apellidos_query);
  apellidos_compl->setCompletionColumn(0);
  apellidos_compl->setCaseSensitivity(Qt::CaseInsensitive);

  ui->txtApellidos->setCompleter(apellidos_compl);

  diocesis_query->setQuery(
      "SELECT DISTINCT birth_diocesis FROM persons WHERE birth_diocesis IS NOT "
      "NULL ORDER BY birth_diocesis");
  diocesis_compl->setModel(diocesis_query);
  diocesis_compl->setCompletionColumn(0);
  diocesis_compl->setCaseSensitivity(Qt::CaseInsensitive);

  ui->txtDiocesis->setCompleter(diocesis_compl);

  QStringList tipos_persona;
  tipos_persona << "Fraile"
                << "Terciario"
                << "Lego"
                << "Monja"
                << "Profeso"
                << "Converso";
  tipopersona_compl = new QCompleter(tipos_persona, this);
  tipopersona_compl->setCaseSensitivity(Qt::CaseInsensitive);
  ui->txtTipoPersona->setCompleter(tipopersona_compl);
}

void dlgNuevaPersona::aceptarPersona()
{
  Persona *persona = new Persona();

  QString nombre = ui->txtNombre->text();
  QString apellidos = ui->txtApellidos->text();
  QString origen = ui->txtOrigen->text();
  bool masculino = ui->ckMasculino->checkState();
  bool buscado = ui->ckBuscado->checkState();
  bool wiki = ui->ckWiki->checkState();
  bool viaf = ui->ckViaf->checkState();
  QString tipo_persona = ui->txtTipoPersona->text();
  QString wikilink = ui->txtWiki->text();
  QString viaflink = ui->txtViaf->text();
  QString wikidata = ui->txtWikidata->text();
  QString notas = ui->txtNotas->toPlainText();
  QString nacimiento = ui->txtNacimiento->text();
  QString muerte = ui->txtMuerte->text();
  QString diocesis = ui->txtDiocesis->text();
  bool volveramirar = ui->ckVolverMirar->checkState();
  int cantidadinfo = ui->spCantidadInfo->value();

  QString otrosnombres;

  // entiendo q solo hay un qvector en este otrosnombres_json, no?
  if (otrosnombres_json->getSize() > 0) {
    qDebug() << "estamos aquí";
    otrosnombres = otrosnombres_json->getJsonString(0);
  }
  else
    otrosnombres = "";

  qDebug() << "los otros nombres son: " << otrosnombres;

  persona->setNombre(nombre);
  persona->setApellidos(apellidos);
  persona->setOrigen(origen);
  persona->setMasculino(masculino);
  persona->setBuscado(buscado);
  persona->setWiki(wiki);
  persona->setViaf(viaf);
  persona->setWikilink(wikilink);
  persona->setViaflink(viaflink);
  persona->setWikidata(wikidata);
  persona->setTipoPersona(tipo_persona);
  persona->setNacimiento(nacimiento);
  persona->setMuerte(muerte);
  persona->setDiocesis(diocesis);
  persona->setVolverMirar(volveramirar);
  persona->setCantidadInfo(cantidadinfo);
  persona->setOtrosnombres(otrosnombres);
  persona->setNotas(notas);
  persona->setFuente(fuente_origen);

  if (!modificando)
    introducirPersonaEnBD(persona);
  else
    introducirPersonaEnBD(persona, true);

  if (modificando) cerrar();
}

void dlgNuevaPersona::on_btDetalles_clicked()
{
  dlgdetalles = new dlgDetalles(jsongestor, PERSONADETALLES, false, this);
  QMdiSubWindow *window = mdiarea->addSubWindow(dlgdetalles);
  window->show();
}

void dlgNuevaPersona::introducirJson(const int id)
{
  QSqlQuery query;
  int totaljson;

  totaljson = jsongestor->getSize();

  if (totaljson == 0) return;

  for (int var = 0; var < totaljson; ++var) {
    QString jsonfinal = jsongestor->getJsonString(var);

    query.prepare(
        "INSERT INTO persons_details(person_id, details) VALUES(:personid, "
        ":json)");
    query.bindValue(":personid", id);
    query.bindValue(":json", jsonfinal);
    query.exec();
  }
}

void dlgNuevaPersona::cargarUI()
{
  mdiarea = MyQmdiArea::Instance(this);

  m_personas = PersonasModel::InstanceModel();

  connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
  connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarPersona()));

  jsongestor = new QJsonModel(this);
  otrosnombres_json = new QJsonModel(this);

  cargarCompleters();
}

void dlgNuevaPersona::on_btOtrosNombres_clicked()
{
  dlgotrosnombres = new dlgDetalles(otrosnombres_json, OTROS, false, this);
  QMdiSubWindow *window = mdiarea->addSubWindow(dlgotrosnombres);
  window->show();
}

void dlgNuevaPersona::cerrar() { parentWidget()->close(); }

void dlgNuevaPersona::borrarCampos()
{
  ui->txtNombre->setText("");
  ui->txtApellidos->setText("");
  ui->txtMuerte->setText("");
  ui->txtNacimiento->setText("");
  ui->txtViaf->setText("");
  ui->txtWiki->setText("");
  ui->txtWikidata->setText("");
  ui->txtNotas->clear();

  ui->ckBuscado->setCheckState(Qt::Unchecked);
  ui->ckViaf->setCheckState(Qt::Unchecked);
  ui->ckWiki->setCheckState(Qt::Unchecked);
  ui->ckVolverMirar->setCheckState(Qt::Unchecked);

  ui->txtNotas->clear();

  /*
   * recargamos/vaciamos las clases json donde guardo
   * diversos tipos de datos.
   * De todas formas: no sé si hay una forma mejor...
   */
  jsongestor = new QJsonModel(this);
  otrosnombres_json = new QJsonModel(this);

  ui->txtNombre->setFocus();
}

void dlgNuevaPersona::cargarPersona()
{
  QSqlQuery query;
  Persona *personaCargada = new Persona();

  personaCargada = m_personas->devolverPersona(persona_modificando);
  jsongestor = m_personas->devolverDetalles(persona_modificando);

  ui->txtNombre->setText(personaCargada->getNombre());
  ui->txtApellidos->setText(personaCargada->getApellidos());
  ui->txtOrigen->setText(personaCargada->getOrigen());
  ui->txtNacimiento->setText(personaCargada->getNacimiento());
  ui->txtMuerte->setText(personaCargada->getMuerte());
  ui->txtDiocesis->setText(personaCargada->getDiocesis());

  ui->ckMasculino->setChecked(personaCargada->getMasculino());
  ui->txtTipoPersona->setText(personaCargada->getTipoPersona());
  ui->ckBuscado->setChecked(personaCargada->getBuscado());
  ui->ckWiki->setChecked(personaCargada->getWiki());
  ui->txtWiki->setText(personaCargada->getWikilink());
  ui->ckViaf->setChecked(personaCargada->getViaf());
  ui->txtViaf->setText(personaCargada->getViaflink());
  ui->txtWikidata->setText(personaCargada->getWikidata());

  ui->ckVolverMirar->setChecked(personaCargada->getVolverMirar());
  ui->spCantidadInfo->setValue(personaCargada->getCantidadInfo());
  ui->txtNotas->setText(personaCargada->getNotas());
}

// esto es para el caso en el que la persona es nueva...
void dlgNuevaPersona::introducirPersonaEnBD(Persona *persona)
{
  if (m_personas->AnadirPersona(persona)) {
    QSqlQuery lastid("select max(person_id) from persons");

    lastid.first();
    int id = lastid.value(0).toInt();
    introducirJson(id);
    borrarCampos();
    cargarCompleters();
    emit personaIntroducida();
    return;
  }
  else {
    int ret =
        QMessageBox::warning(this, "Error al introducir la resolución",
                             "Error al introducir la resolución en la BD");
    Q_UNUSED(ret)
    return;
  }
}

/*
 * Para cuando la obra ya existe... Aquí la clave es que hacemos una cosa tosca:
 * borramos todos los temas y todos los detalles y de las tablas
 * correspondientes y volvemos a añadir los datso de esas tablas desde cero.
 */
void dlgNuevaPersona::introducirPersonaEnBD(Persona *persona, bool modificar)
{
  Q_UNUSED(modificar)

  QSqlQuery query;

  if (m_personas->AnadirPersona(persona, persona_modificando)) {
    query.exec(QString("DELETE FROM persons_details WHERE person_id = %1")
                   .arg(persona_modificando));
    introducirJson(persona_modificando);
    borrarCampos();
    cargarCompleters();
    emit personaIntroducida();
    return;
  }
  else {
    int ret =
        QMessageBox::warning(this, "Error al introducir la resolución",
                             "Error al introducir la resolución en la BD");
    Q_UNUSED(ret)
    return;
  }
}

void dlgNuevaPersona::on_btFuente_clicked()
{
  dlgFuenteEntrada *dlgfuente = new dlgFuenteEntrada(this);
  connect(dlgfuente, SIGNAL(signalFuente(fuente)), this,
          SLOT(recibirFuente(fuente)));

  dlgfuente->show();
}

void dlgNuevaPersona::recibirFuente(fuente f)
{
  // esto no lo complico un poco?
  QJsonObject fuente_json;
  QJsonObject fuente_final;

  fuente_json.insert("source_id", QJsonValue(f.titulo));
  fuente_json.insert("volume", f.tomo);
  fuente_json.insert("pages", f.paginas);

  fuente_final.insert("source", fuente_json);

  jsongestor->anadirJson(fuente_final);
}
