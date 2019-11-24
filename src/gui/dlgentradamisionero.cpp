#include "dlgentradamisionero.h"

#include <QDebug>
#include <QJsonDocument>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

#include "dlgfuenteentrada.h"
#include "dlgseleccionargeneral.h"
#include "src/widgets/myqmdiarea.h"
#include "ui_dlgentradamisionero.h"

dlgEntradaMisionero::dlgEntradaMisionero(int mision, QWidget *parent)
    : QWidget(parent), ui(new Ui::dlgEntradaMisionero), mision_id(mision)
{
  ui->setupUi(this);
  mdiarea = MyQmdiArea::Instance(this);

  // hay que inicializar el pointer para que no dé error luego.
  fuentedatos = new QJsonObject();

  connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(cerrar()));
  connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarMisionero()));
  connect(ui->btFuente, SIGNAL(clicked()), this, SLOT(anadirFuente()));
  connect(ui->txtPersona, SIGNAL(dobleclick()), this, SLOT(anadirPersona()));
}

dlgEntradaMisionero::~dlgEntradaMisionero() { delete ui; }

void dlgEntradaMisionero::anadirPersona()
{
  dlgSeleccionarGeneral *seleccionar =
      new dlgSeleccionarGeneral(PERSONA, true, this);
  connect(seleccionar, SIGNAL(personaEscogidaSignal(Persona)), this,
          SLOT(recibirPersona(Persona)));

  QMdiSubWindow *window = mdiarea->addSubWindow(seleccionar);
  window->show();
}

void dlgEntradaMisionero::anadirFuente()
{
  dlgFuenteEntrada *dlgfuente = new dlgFuenteEntrada(this);
  connect(dlgfuente, SIGNAL(signalFuente(fuente)), this,
          SLOT(recibirFuente(fuente)));

  dlgfuente->show();
}

void dlgEntradaMisionero::recibirPersona(Persona persona)
{
  persona_id = persona.getId();
  ui->txtPersona->setText(persona.getNombreCompleto());
}

void dlgEntradaMisionero::recibirFuente(fuente datoobra)
{
  QJsonObject json_datosconcretos;

  fuente_recibida = true;

  json_datosconcretos.insert("source_id", QJsonValue(datoobra.titulo));
  json_datosconcretos.insert("volume", datoobra.tomo);
  json_datosconcretos.insert("pages", datoobra.paginas);

  fuentedatos->insert("source", json_datosconcretos);
}

void dlgEntradaMisionero::cerrar() { parentWidget()->close(); }

void dlgEntradaMisionero::aceptarMisionero()
{
  QSqlQuery query;

  if (persona_id == 0) {
    int ret = QMessageBox::warning(this, "Faltan datos",
                                   "Falta la persona del misionero.");
    Q_UNUSED(ret)
    return;
  }

  bool llego = ui->ckLlego->isChecked();
  bool volver_mirar = ui->ckVolverMirar->isChecked();
  bool volvio = ui->ckRegreso->isChecked();
  int cantidad_info = ui->spCantidadInfo->value();
  QString notas = ui->txtNotas->toPlainText();

  /*
   * ATENCIÓn: aquí lo que hago es dereferenciar un pointer,
   * porque QJsonDocument me pide una referencia y fuentedatos
   * es un pointer...
   */
  QJsonDocument jsondoc(*fuentedatos);
  QString fuente_final = jsondoc.toJson(QJsonDocument::Compact);

  query.prepare(
      "INSERT INTO filipinas.missions_persons(mission_id, person_id, "
      "arrived, returned, info, see_again, info_source, notes) "
      "VALUES(:mision, :persona, "
      ":llego, :volvio, :info, :volver_mirar, :fuente, :notas)");
  query.bindValue(":mision", mision_id);
  query.bindValue(":persona", persona_id);
  query.bindValue(":llego", llego);
  query.bindValue(":volvio", volvio);
  query.bindValue(":info", cantidad_info);
  query.bindValue(":volver_mirar", volver_mirar);
  query.bindValue(":notas", notas);

  if (fuente_recibida)
    query.bindValue(":fuente", fuente_final);
  else
    query.bindValue(":fuente", QVariant(QVariant::String));

  if (query.exec()) {
    borrarCampos();
  }
  else {
    int ret = QMessageBox::warning(
        this, "Error",
        "Ha habido un error al ejecutar la consulta de inserción.");
    Q_UNUSED(ret)
    qDebug() << query.lastError();
    return;
  }
}

void dlgEntradaMisionero::borrarCampos()
{
  persona_id = 0;
  ui->txtPersona->clear();

  ui->ckLlego->setCheckState(Qt::Unchecked);
  ui->ckRegreso->setCheckState(Qt::Unchecked);
  ui->ckVolverMirar->setCheckState(Qt::Unchecked);
  ui->spCantidadInfo->setValue(100);

  ui->txtNotas->setText("");

  /*
   * no borramos el punto fuentedatos
   * pque ahora no sé cómo borrar un pointer
   * pero en principio conesta variable debería ser
   * suficiente
   */
  // fuentedatos = QJsonObject();
  fuente_recibida = false;
}
