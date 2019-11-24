#include "dlgdeclaracionentrada.h"

#include <QMdiSubWindow>

#include "dlginfraccionentrada.h"
#include "dlgpenaentrada.h"
#include "src/models/qjsonmodel.h"
#include "src/widgets/myqmdiarea.h"
#include "ui_dlgdeclaracionentrada.h"

// TODO: falta añadir lo de persona, pero no sé para qué lo puse...

dlgDeclaracionEntrada::dlgDeclaracionEntrada(QWidget *parent)
    : QDialog(parent), ui(new Ui::dlgDeclaracionEntrada)
{
  ui->setupUi(this);

  mdiarea = MyQmdiArea::Instance(this);

  json_model_infracciones = new QJsonModel(this);
  ui->twJsonInfraccion->setModel(json_model_infracciones);

  connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
  connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
  connect(ui->btInfraccion, SIGNAL(clicked(bool)), this,
          SLOT(anadirInfraccion()));
  connect(ui->btPena, SIGNAL(clicked(bool)), this, SLOT(anadirPena()));
  connect(ui->wdNotas, SIGNAL(textoIntroducido()), this,
          SLOT(notaIntroducida()));
}

dlgDeclaracionEntrada::~dlgDeclaracionEntrada() { delete ui; }

void dlgDeclaracionEntrada::aceptar()
{
  QString tipo = ui->txtTipo->text();
  ExtraInfos e = ui->wdExtras->getExtraInfos();

  declaracion.setPena(pena_estipulada);
  declaracion.setInfraccion(infraccion_cometida);
  declaracion.setTipo(tipo);
  declaracion.setExtraInfos(e);

  if (ui->wdNotas->haCambiado()) declaracion.setNota(ui->wdNotas->getNotas());

  emit(aceptarDeclaracion(declaracion));

  close();
}

void dlgDeclaracionEntrada::anadirInfraccion()
{
  dlgInfraccionEntrada *dlginfraccion = new dlgInfraccionEntrada(this);
  connect(dlginfraccion, SIGNAL(aceptarInfraccion(Infraccion)), this,
          SLOT(recibirInfraccion(Infraccion)));

  QMdiSubWindow *window = mdiarea->addSubWindow(dlginfraccion);
  window->show();
}

void dlgDeclaracionEntrada::anadirPena()
{
  dlgPenaEntrada *dlgpena = new dlgPenaEntrada(this);
  connect(dlgpena, SIGNAL(aceptarPena(Pena)), this, SLOT(recibirPena(Pena)));

  QMdiSubWindow *window = mdiarea->addSubWindow(dlgpena);
  window->show();
}

void dlgDeclaracionEntrada::recibirInfraccion(Infraccion infraccion)
{
  infraccion_cometida = infraccion;
  QJsonObject infraccion_json = infraccion.getInfraccionJson();
  json_model_infracciones->anadirJson(infraccion_json);
  json_model_infracciones->resetearModelo();
}

void dlgDeclaracionEntrada::recibirPena(Pena pena) { pena_estipulada = pena; }

void dlgDeclaracionEntrada::cerrar() { parentWidget()->close(); }
