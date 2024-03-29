#include "mainwindow.h"

#include <QDebug>
#include <QInputDialog>
#include <QLabel>
#include <QMdiSubWindow>
#include <QSqlTableModel>
#include <QtGui>

#include "dlganneenuevo.h"
#include "dlgcapitulos.h"
#include "dlgciudades.h"
#include "dlgdiocesis.h"
#include "dlgestadisticas.h"
#include "dlggestioncasas.h"
#include "dlggestionobras.h"
#include "dlggestionpersonas.h"
#include "dlgmisiones.h"
#include "dlgnuevacasa.h"
#include "dlgnuevadiocesis.h"
#include "dlgnuevafuente.h"
#include "dlgnuevamisionfilipinas.h"
#include "dlgnuevaobra.h"
#include "dlgnuevapersona.h"
#include "dlgnuevaprovincia.h"
#include "dlgnuevaresolucion.h"
#include "dlgnuevocapitulo.h"
#include "dlgnuevoobispo.h"
#include "dlgobispos.h"
#include "dlgreforma.h"
#include "dlgresoluciones.h"
#include "ui_mainwindow.h"

// para lo de MDIarea
#include "dlgdetalles.h"
#include "src/models/capitulosmodel.h"
#include "src/models/casasmodel.h"
#include "src/models/lugaresmodel.h"
#include "src/models/obrasmodel.h"
#include "src/models/personasmodel.h"
#include "src/models/provinciasmodel.h"
#include "src/models/qjsonmodel.h"
#include "src/models/temasmodel.h"
#include "src/objs/tema.h"
#include "src/widgets/barralabel.h"
#include "src/widgets/myqmdiarea.h"

const int STATUSBAR_TIMEOUT = 1000;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  mdiArea = MyQmdiArea::Instance(this);

  setCentralWidget(mdiArea);
  QMainWindow::showMaximized();

  info_statusbar = new BarraLabel(this);
  info_idbar = new BarraLabel(this);
  statusBar()->addPermanentWidget(info_idbar);
  statusBar()->addPermanentWidget(info_statusbar);

  db = QSqlDatabase::addDatabase("QPSQL");
  db.setHostName("localhost");
  db.setDatabaseName("dominicos");
  // db.setDatabaseName("domis");
  db.setUserName("igor");

  if (db.open()) qDebug() << "Abierta";

  cargarModelos();
  cargarMenues();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::cargarMenues()
{
  statusBar()->showMessage("Cargando los menúes", STATUSBAR_TIMEOUT);

  connect(ui->actionNuevoCapitulo, SIGNAL(triggered()), this,
          SLOT(nuevoCapitulo()));
  connect(ui->actionNuevaCasa, SIGNAL(triggered()), this, SLOT(nuevaCasa()));
  connect(ui->actionNuevaPersona, SIGNAL(triggered()), this,
          SLOT(nuevaPersona()));
  connect(ui->actionNuevaObra, SIGNAL(triggered()), this, SLOT(nuevaObra()));
  connect(ui->actionNuevaProvincia, SIGNAL(triggered()), this,
          SLOT(nuevaProvincia()));
  connect(ui->actionNuevaDiocesis, SIGNAL(triggered()), this,
          SLOT(nuevaDiocesis()));
  connect(ui->actionNuevoTema, SIGNAL(triggered()), this, SLOT(nuevoTema()));
  connect(ui->actionNuevaResolucion, SIGNAL(triggered(bool)), this,
          SLOT(nuevaResolucion()));
  connect(ui->actionNuevoObispo, SIGNAL(triggered(bool)), this,
          SLOT(nuevoObispo()));
  connect(ui->actionNuevaMision, SIGNAL(triggered(bool)), this,
          SLOT(nuevaMision()));
  connect(ui->actionNuevaFuente, SIGNAL(triggered(bool)), this,
          SLOT(nuevaFuente()));
  connect(ui->actionIntroducirReformaConvento, SIGNAL(triggered(bool)), this,
          SLOT(nuevaReforma()));
  connect(ui->actionNuevoAnnee, SIGNAL(triggered(bool)), this,
          SLOT(nuevoAnnee()));

  connect(ui->actionResoluciones, SIGNAL(triggered(bool)), this,
          SLOT(Resoluciones()));
  connect(ui->actionCiudades, SIGNAL(triggered(bool)), this, SLOT(Ciudades()));
  connect(ui->actionCasas, SIGNAL(triggered(bool)), this, SLOT(Casas()));
  connect(ui->actionMisiones, SIGNAL(triggered(bool)), this, SLOT(Misiones()));
  connect(ui->actionDiocesis, SIGNAL(triggered(bool)), this, SLOT(Diocesis()));
  connect(ui->actionCapituli, SIGNAL(triggered(bool)), this, SLOT(Capitulos()));
  connect(ui->actionObras, SIGNAL(triggered(bool)), this, SLOT(Obras()));
  connect(ui->actionPersonas, SIGNAL(triggered(bool)), this, SLOT(Personas()));

  connect(ui->actionGeneralEstadisticas, SIGNAL(triggered(bool)), this,
          SLOT(Estadisticas()));
  connect(ui->actionSalir, SIGNAL(triggered()), qApp, SLOT(quit()));

  statusBar()->showMessage("Menúes cargados", STATUSBAR_TIMEOUT);
}

void MainWindow::inicializarBarraEstadisticas()
{
  /*
   * Ponemos tanto los totales como los filtrados aquí al inicio
   * pq así es más fácil al inicializar de crear la frasecita
   */
  info_statusbar->setNumeroCasasTotal(m_casas->rowCount());
  info_statusbar->setNumeroCiudadesTotal(m_lugares->rowCount());
  info_statusbar->setNumeroPersonasTotal(m_personas->rowCount());
  info_statusbar->setNumeroObrasTotal(m_obras->rowCount());
  info_statusbar->setNumeroCasasFiltrados(m_casas->rowCount());
  info_statusbar->setNumeroCiudadesFiltrados(m_lugares->rowCount());
  info_statusbar->setNumeroPersonasFiltrados(m_personas->rowCount());
  info_statusbar->setNumeroObrasFiltrados(m_obras->rowCount());

  info_statusbar->inicializar();
}

void MainWindow::nuevoCapitulo()
{
  dlgCapitulo = new dlgNuevoCapitulo(this);
  QMdiSubWindow *window = mdiArea->addSubWindow(dlgCapitulo);
  window->show();
}

void MainWindow::cargarModelos()
{
  statusBar()->showMessage("Cargando los modelos", STATUSBAR_TIMEOUT);

  m_temas = TemasModel::InstanceModel();
  // esto no habría que ponerlo en el constructor de la clase?
  m_temas->setSort(1, Qt::AscendingOrder);
  m_temas->select();

  m_lugares = LugaresModel::InstanceModel();
  m_lugares->setSort(1, Qt::AscendingOrder);
  m_lugares->select();

  m_personas = PersonasModel::InstanceModel();

  m_casas = CasasModel::InstanceModel();

  m_provincias = ProvinciasModel::InstanceModel();
  m_provincias->setSort(1, Qt::AscendingOrder);
  m_provincias->select();

  m_capitulos = CapitulosModel::InstanceModel();
  m_capitulos->select();

  m_obras = ObrasModel::InstanceModel();
  m_obras->select();

  statusBar()->showMessage("Modelos cargados", STATUSBAR_TIMEOUT);

  inicializarBarraEstadisticas();
}

void MainWindow::nuevaResolucion()
{
  dlgResolucion = new dlgNuevaResolucion(0, this);
  connect(dlgResolucion, SIGNAL(abrirDetalles(dlgDetalles *)), this,
          SLOT(abrirDetalles(dlgDetalles *)));
  QMdiSubWindow *window = mdiArea->addSubWindow(dlgResolucion);
  window->show();
}

void MainWindow::nuevaPersona()
{
  dlgPersona = new dlgNuevaPersona(this);
  QMdiSubWindow *window = mdiArea->addSubWindow(dlgPersona);
  window->show();
}

void MainWindow::nuevaCasa()
{
  // dlgCasa = new dlgNuevaCasa(this);
  // hay q poner this o poner ui->mdiArea como parent?
  dlgCasa = new dlgNuevaCasa(this, 0);
  QMdiSubWindow *window = mdiArea->addSubWindow(dlgCasa);
  window->show();
}

void MainWindow::nuevaDiocesis()
{
  dlgMeterNuevaDiocesis = new dlgNuevaDiocesis(this);
  QMdiSubWindow *window = mdiArea->addSubWindow(dlgMeterNuevaDiocesis);
  window->show();
}

void MainWindow::nuevoObispo()
{
  dlgObispo = new dlgNuevoObispo(this);
  QMdiSubWindow *window = mdiArea->addSubWindow(dlgObispo);
  window->show();
}

void MainWindow::nuevaMision()
{
  dlgNuevaMision = new dlgNuevaMisionFilipinas(this);
  QMdiSubWindow *window = mdiArea->addSubWindow(dlgNuevaMision);
  window->show();
}

void MainWindow::Capitulos()
{
  FormCapitulos = new dlgCapitulos(this);
  FormCapitulos->show();
}

void MainWindow::Resoluciones()
{
  FormResoluciones = new dlgResoluciones(this);
  QMdiSubWindow *window = mdiArea->addSubWindow(FormResoluciones);
  window->show();
}

void MainWindow::Ciudades()
{
  FormCiudades = new dlgCiudades(this);
  QMdiSubWindow *window = mdiArea->addSubWindow(FormCiudades);
  window->show();
}

void MainWindow::Casas()
{
  FormCasas = new dlgGestionCasas(this);
  connect(FormCasas, SIGNAL(infoBarra(int)), info_statusbar,
          SLOT(setNumeroCasasFiltrados(int)));
  QMdiSubWindow *window = mdiArea->addSubWindow(FormCasas);
  window->show();
}

void MainWindow::Misiones()
{
  FormMisiones = new dlgMisiones(this);
  QMdiSubWindow *window = mdiArea->addSubWindow(FormMisiones);
  window->show();
}

void MainWindow::Diocesis()
{
  FormDiocesis = new dlgDiocesis(this);
  QMdiSubWindow *window = mdiArea->addSubWindow(FormDiocesis);
  window->show();
}

void MainWindow::Obras()
{
  GestionObras = new dlgGestionObras(this);
  QMdiSubWindow *window = mdiArea->addSubWindow(GestionObras);
  connect(GestionObras, SIGNAL(infoBarra(int)), info_statusbar,
          SLOT(setNumeroObrasFiltrados(int)));
  connect(GestionObras, SIGNAL(infoObraSeleccionada(QString)), this,
          SLOT(updateStatusBarIdSeleccionado(QString)));
  connect(GestionObras, SIGNAL(infoObraSeleccionadaBorrar()), this,
          SLOT(updateStatusBarIdSeleccionadoBorrar()));

  window->show();
}

void MainWindow::Personas()
{
  GestionPersonas = new dlgGestionPersonas(this);
  QMdiSubWindow *window = mdiArea->addSubWindow(GestionPersonas);

  connect(GestionPersonas, SIGNAL(infoBarra(int)), info_statusbar,
          SLOT(setNumeroPersonasFiltrados(int)));
  connect(GestionPersonas, SIGNAL(infoPersonaSeleccionada(QString)), this,
          SLOT(updateStatusBarIdSeleccionado(QString)));
  connect(GestionPersonas, SIGNAL(infoPersonaSeleccionadaBorrar()), this,
          SLOT(updateStatusBarIdSeleccionadoBorrar()));

  window->show();
}

void MainWindow::Estadisticas()
{
  FormEstadisticas = new dlgEstadisticas(this);
  QMdiSubWindow *window = mdiArea->addSubWindow(FormEstadisticas);
  window->show();
}

void MainWindow::abrirDetalles(dlgDetalles *dlg)
{
  QMdiSubWindow *window = mdiArea->addSubWindow(dlg);
  window->show();
}

void MainWindow::nuevaObra()
{
  dlgNuevaObra *nuevaObra = new dlgNuevaObra(this);
  QMdiSubWindow *window = mdiArea->addSubWindow(nuevaObra);
  window->show();
}

void MainWindow::nuevaProvincia()
{
  dlgNuevaProvincia *dlgprovincia = new dlgNuevaProvincia(this);
  dlgprovincia->show();
}

void MainWindow::nuevoTema()
{
  Tema *tema = new Tema();

  QString tematitulo =
      QInputDialog::getText(this, "Introduzca nuevo tema", "Nueva tema");

  if (!tematitulo.isEmpty()) {
    tema->setTema(tematitulo);
    m_temas->AnadirTema(tema);
  }
}

void MainWindow::nuevaFuente()
{
  dlgNuevaFuente *nuevaFuente = new dlgNuevaFuente(this);
  nuevaFuente->show();
}

void MainWindow::nuevaReforma()
{
  dlgReforma *dlgReformaConvento = new dlgReforma(this);

  dlgReformaConvento->show();
}

void MainWindow::nuevoAnnee()
{
  dlgAnnee = new dlgAnneeNuevo(this);
  QMdiSubWindow *window = mdiArea->addSubWindow(dlgAnnee);
  window->show();
}

void MainWindow::on_actionObispos_triggered()
{
  FormObispos = new dlgObispos(this);
  QMdiSubWindow *window = mdiArea->addSubWindow(FormObispos);
  window->show();

  connect(FormObispos, SIGNAL(infoBarraInferior(QString)), this,
          SLOT(updateStatusBarDerecha(QString)));

  FormObispos->contarTotal();
}

void MainWindow::updateStatusBarDerecha(QString mensaje)
{
  info_statusbar->setText(mensaje);
}

void MainWindow::updateStatusBarIdSeleccionado(const QString mensaje)
{
  info_idbar->setText(mensaje);
}

void MainWindow::updateStatusBarIdSeleccionadoBorrar() { info_idbar->clear(); }
