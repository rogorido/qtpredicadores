#include "dlgnuevacasa.h"

#include <QCompleter>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>

#include "dlgfuenteentrada.h"
#include "dlgseleccionargeneral.h"
#include "src/models/casasmodel.h"
#include "src/models/lugaresmodel.h"
#include "src/models/provinciasmodel.h"
#include "src/objs/casa.h"
#include "src/objs/variados.h"
#include "src/widgets/myqmdiarea.h"
#include "ui_dlgnuevacasa.h"

dlgNuevaCasa::dlgNuevaCasa(QWidget *parent, int casa)
    : QWidget(parent), ui(new Ui::dlgNuevaCasa)
{
  ui->setupUi(this);

  mdiarea = MyQmdiArea::Instance(this);

  fuentedatos = new QJsonObject();

  m_lugares = LugaresModel::InstanceModel();
  m_casas = CasasModel::InstanceModel();

  ui->txtProvincia->setClearButtonEnabled(true);
  ui->txtLugar->setClearButtonEnabled(true);

  connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(cerrar()));
  connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarCasa()));
  connect(ui->txtLugar, SIGNAL(dobleclick()), this, SLOT(anadirLugar()));
  connect(ui->btQuitarLugar, SIGNAL(clicked()), this, SLOT(quitarLugar()));
  connect(ui->txtProvincia, SIGNAL(dobleclick()), this,
          SLOT(anadirProvincia()));
  connect(ui->btFuente, SIGNAL(clicked(bool)), this, SLOT(anadirFuente()));

  cargarModelos();

  if (casa != 0) {
    modificando = true;
    casa_modificando = casa;
    cargarCasa();
  }

  ui->txtNombre->setFocus();
}

dlgNuevaCasa::~dlgNuevaCasa() { delete ui; }

void dlgNuevaCasa::aceptarCasa()
{
  Casa *casa = new Casa();

  QString nombre = ui->txtNombre->text();
  int lugar;
  int provincia;
  bool buscado = ui->ckBuscado->checkState();
  bool masculino = ui->ckMasculino->checkState();
  bool wiki = ui->ckWiki->checkState();
  QString tipo = ui->txtTipo->text();
  QString advocacion = ui->txtAdvocacion->text();
  QString diocesis = ui->txtDiocesis->text();
  // este  sería interesante hacerlo con QJson...
  // QString otrosnombres;
  bool quetif = ui->ckQuetif->checkState();
  QString fechafundacion = ui->txtFechaFundacion->text();
  QString fechaeliminacion = ui->txtEliminada->text();
  QString notas = ui->txtNotas->toPlainText();
  bool studiumgenerale = ui->ckStudium->checkState();
  QString otrosdatos;  // aquí va el json de la fuente

  /*
   * hay que comprobar que esté vacío?
   * entiendo q un struct no se puede comprobar... además de que
   * vacío no puede estar pq lo inicializo. Comprobamos que no sea 0
   * abajo al meterlo en la clase Casa.
   */
  lugar = lugar_struct.id;
  provincia = provincia_struct.id;

  if (fuente_recibida) {
    /*
     * ATENCIÓn: aquí lo que hago es dereferenciar un pointer,
     * porque QJsonDocument me pide una referencia y fuentedatos
     * es un pointer...
     */
    QJsonDocument jsondoc(*fuentedatos);
    otrosdatos = jsondoc.toJson(QJsonDocument::Compact);
  }
  else {
    otrosdatos = "";
  }

  casa->setNombre(nombre);
  if (lugar != 0) casa->setLugar(lugar);
  if (provincia != 0) casa->setProvincia(provincia);
  casa->setBuscado(buscado);
  casa->setWiki(wiki);
  casa->setTipo(tipo);
  casa->setAdvocacion(advocacion);
  casa->setDiocesis(diocesis);
  casa->setQuetif(quetif);
  casa->setMasculino(masculino);
  casa->setFechaFundacion(fechafundacion);
  casa->setFechaEliminacion(fechaeliminacion);
  casa->setNotas(notas);
  casa->setStudiumgenerale(studiumgenerale);

  if (m_casas->AnadirCasa(casa)) {
    emit casaIntroducida();
    borrarCampos();
  }
  else {
    int ret = QMessageBox::warning(this, "Error al introducir la casa",
                                   "Error al introducir la casa en la BD");
    Q_UNUSED(ret)
    return;
  }
}

void dlgNuevaCasa::anadirLugar()
{
  dlgSeleccionarGeneral *dlgSeleccionar =
      new dlgSeleccionarGeneral(LUGAR, true, this);
  connect(dlgSeleccionar, SIGNAL(lugarEscogidoSignal(Lugar)), this,
          SLOT(recibirLugar(Lugar)));

  QMdiSubWindow *window = mdiarea->addSubWindow(dlgSeleccionar);
  window->show();
}

void dlgNuevaCasa::recibirLugar(Lugar lugarescogido)
{
  lugar_struct.id = lugarescogido.getId();
  lugar_struct.elemento = lugarescogido.getLugar();

  ui->txtLugar->setText(lugar_struct.elemento);
}

void dlgNuevaCasa::anadirFuente()
{
  dlgFuenteEntrada *dlgfuente = new dlgFuenteEntrada(this);
  connect(dlgfuente, SIGNAL(signalFuente(fuente)), this,
          SLOT(recibirFuente(fuente)));

  dlgfuente->show();
}

void dlgNuevaCasa::quitarLugar() { lugar_struct = elementopareado(); }

void dlgNuevaCasa::anadirProvincia()
{
  dlgSeleccionarGeneral *dlgSeleccionar =
      new dlgSeleccionarGeneral(PROVINCIA, true, this);
  connect(dlgSeleccionar, SIGNAL(provinciaEscogidaSignal(Provincia)), this,
          SLOT(recibirProvincia(Provincia)));

  QMdiSubWindow *window = mdiarea->addSubWindow(dlgSeleccionar);
  window->show();
}

void dlgNuevaCasa::recibirProvincia(Provincia provincia)
{
  provincia_struct.id = provincia.getId();
  provincia_struct.elemento = provincia.getNombre();

  ui->txtProvincia->setText(provincia_struct.elemento);
}

void dlgNuevaCasa::recibirFuente(fuente f)
{
  fuente_recibida = true;

  fuentedatos->insert("book", QJsonValue(f.titulo));
  fuentedatos->insert("volume", f.tomo);
  fuentedatos->insert("pages", f.paginas);
}

void dlgNuevaCasa::cerrar() { this->parentWidget()->close(); }

void dlgNuevaCasa::quitarProvincia()
{
  provincia_struct = elementopareado();
  ui->txtProvincia->setText("");
}

void dlgNuevaCasa::borrarCampos()
{
  ui->txtNombre->setText("");
  ui->txtLugar->setText("");
  ui->txtLugarOriginario->setText("");
  ui->txtProvincia->setText("");
  ui->txtTipo->setText("");
  ui->txtAdvocacion->setText("");
  ui->txtDiocesis->setText("");
  ui->txtFechaFundacion->setText("");
  ui->txtEliminada->setText("");
  ui->txtNotas->clear();

  ui->ckBuscado->setCheckState(Qt::Unchecked);
  ui->ckMasculino->setCheckState(Qt::Unchecked);
  ui->ckStudium->setCheckState(Qt::Unchecked);
  ui->ckWiki->setCheckState(Qt::Unchecked);

  lugar_struct = elementopareado();
  provincia_struct = elementopareado();

  ui->txtNombre->setFocus();
}

void dlgNuevaCasa::cargarModelos()
{
  m_tipos = new QSqlQueryModel(this);
  m_tipos_completer = new QCompleter(this);

  m_tipos->setQuery(
      "SELECT DISTINCT type_house FROM general.houses ORDER BY type_house");
  m_tipos_completer->setModel(m_tipos);
  m_tipos_completer->setCompletionColumn(0);
  m_tipos_completer->setCaseSensitivity(Qt::CaseInsensitive);
  ui->txtTipo->setCompleter(m_tipos_completer);

  m_advocaciones = new QSqlQueryModel(this);
  m_advocaciones_completer = new QCompleter(this);

  m_advocaciones->setQuery(
      "SELECT DISTINCT advocation FROM general.houses ORDER BY advocation");
  m_advocaciones_completer->setModel(m_advocaciones);
  m_advocaciones_completer->setCompletionColumn(0);
  m_advocaciones_completer->setCaseSensitivity(Qt::CaseInsensitive);
  ui->txtAdvocacion->setCompleter(m_advocaciones_completer);

  m_diocesis = new QSqlQueryModel(this);
  m_diocesis_completer = new QCompleter(this);

  m_diocesis->setQuery(
      "SELECT DISTINCT diocese FROM general.houses ORDER BY diocese");
  m_diocesis_completer->setModel(m_diocesis);
  m_diocesis_completer->setCompletionColumn(0);
  m_diocesis_completer->setCaseSensitivity(Qt::CaseInsensitive);
  ui->txtDiocesis->setCompleter(m_diocesis_completer);
}

void dlgNuevaCasa::cargarCasa()
{
  QSqlQuery query;
  Casa *casaModificada = new Casa();

  casaModificada = m_casas->devolverCasa(casa_modificando);

  ui->txtNombre->setText(casaModificada->getNombre());
  ui->txtLugar->setText("");
  ui->txtLugarOriginario->setText(casaModificada->getLugarOriginario());
  ui->txtProvincia->setText("");
  ui->txtTipo->setText(casaModificada->getTipo());
  ui->txtAdvocacion->setText(casaModificada->getAdvocacion());
  ui->txtDiocesis->setText(casaModificada->getDiocesis());
  ui->txtFechaFundacion->setText(casaModificada->getFechaFundacion());
  ui->txtEliminada->setText(casaModificada->getFechaEliminacion());
  ui->txtNotas->setText(casaModificada->getNotas());

  ui->ckBuscado->setChecked(casaModificada->getBuscado());
  ui->ckMasculino->setChecked(casaModificada->getMasculino());
  ui->ckStudium->setChecked(casaModificada->getStudiumgenerale());
  ui->ckWiki->setChecked(casaModificada->getWiki());

  // el lugar
  query.exec(QString("SELECT place_id, place FROM places WHERE place_id=%1")
                 .arg(casaModificada->getLugar()));
  query.first();
  // atención: es psoible que este campo esté vacío!
  if (query.size() > 0) {
    lugar_struct.id = casaModificada->getLugar();
    lugar_struct.elemento = query.value(1).toString();
    ui->txtLugar->setText(lugar_struct.elemento);
  }

  // la provincia
  query.exec(
      QString("SELECT province_id, name FROM places WHERE province_id=%1")
          .arg(casaModificada->getProvincia()));
  query.first();
  // atención: es psoible que este campo esté vacío!
  if (query.size() > 0) {
    provincia_struct.id = casaModificada->getProvincia();
    provincia_struct.elemento = query.value(1).toString();
    ui->txtProvincia->setText(provincia_struct.elemento);
  }
}
