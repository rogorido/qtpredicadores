#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QDebug>
#include <QInputDialog>
#include <QSqlTableModel>
#include <QMdiSubWindow>
#include <QLabel>

#include "dlgnuevocapitulo.h"
#include "dlgnuevaresolucion.h"
#include "dlgnuevapersona.h"
#include "dlgnuevacasa.h"
#include "dlgnuevaobra.h"
#include "dlgnuevaprovincia.h"
#include "dlgnuevadiocesis.h"
#include "dlgnuevoobispo.h"
#include "dlgnuevamisionfilipinas.h"
#include "dlgnuevafuente.h"
#include "dlgresoluciones.h"
#include "dlgciudades.h"
#include "dlgcasas.h"
#include "dlgcapitulos.h"
#include "dlgmisiones.h"
#include "dlgestadisticas.h"
#include "dlgreforma.h"
#include "dlgobispos.h"
#include "dlgdiocesis.h"

// para lo de MDIarea
#include "dlgdetalles.h"

#include "widgets/myqmdiarea.h"

#include "models/temasmodel.h"
#include "models/lugaresmodel.h"
#include "models/personasmodel.h"
#include "models/casasmodel.h"
#include "models/provinciasmodel.h"
#include "models/capitulosmodel.h"
#include "models/qjsonmodel.h"

#include "objs/tema.h"

const int STATUSBAR_TIMEOUT = 1000;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mdiArea = MyQmdiArea::Instance(this);

    setCentralWidget(mdiArea);
    QMainWindow::showMaximized();

    info_statusbar = new QLabel(this);
    statusBar()->addPermanentWidget(info_statusbar);

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("dominicos");
    //db.setDatabaseName("domis");
    db.setUserName("igor");

    if (db.open())
        qDebug() << "Abierta";

    cargarModelos();
    cargarMenues();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargarMenues(){

    statusBar()->showMessage("Cargando los menúes", STATUSBAR_TIMEOUT);

    connect(ui->actionNuevoCapitulo, SIGNAL(triggered()), this, SLOT(nuevoCapitulo()));
    connect(ui->actionNuevaCasa, SIGNAL(triggered()), this, SLOT(nuevaCasa()));
    connect(ui->actionNuevaPersona, SIGNAL(triggered()), this, SLOT(nuevaPersona()));
    connect(ui->actionNuevaObra, SIGNAL(triggered()), this, SLOT(nuevaObra()));
    connect(ui->actionNuevaProvincia, SIGNAL(triggered()), this, SLOT(nuevaProvincia()));
    connect(ui->actionNuevaDiocesis, SIGNAL(triggered()), this, SLOT(nuevaDiocesis()));
    connect(ui->actionNuevoTema, SIGNAL(triggered()), this, SLOT(nuevoTema()));
    connect(ui->actionNuevaResolucion, SIGNAL(triggered(bool)), this, SLOT(nuevaResolucion()));
    connect(ui->actionNuevoObispo, SIGNAL(triggered(bool)), this, SLOT(nuevoObispo()));
    connect(ui->actionNuevaMision, SIGNAL(triggered(bool)), this, SLOT(nuevaMision()));
    connect(ui->actionNuevaFuente, SIGNAL(triggered(bool)), this, SLOT(nuevaFuente()));
    connect(ui->actionIntroducirReformaConvento, SIGNAL(triggered(bool)), this, SLOT(nuevaReforma()));
    connect(ui->actionResoluciones, SIGNAL(triggered(bool)), this, SLOT(Resoluciones()));
    connect(ui->actionCiudades, SIGNAL(triggered(bool)), this, SLOT(Ciudades()));
    connect(ui->actionCasas, SIGNAL(triggered(bool)), this, SLOT(Casas()));
    connect(ui->actionMisiones, SIGNAL(triggered(bool)), this, SLOT(Misiones()));
    connect(ui->actionDiocesis, SIGNAL(triggered(bool)), this, SLOT(Diocesis()));
    connect(ui->actionCapituli, SIGNAL(triggered(bool)), this, SLOT(Capitulos()));
    connect(ui->actionGeneralEstadisticas, SIGNAL(triggered(bool)), this, SLOT(Estadisticas()));
    connect(ui->actionSalir, SIGNAL(triggered()), qApp, SLOT(quit()));

    statusBar()->showMessage("Menúes cargados", STATUSBAR_TIMEOUT);
}

void MainWindow::nuevoCapitulo(){

    dlgCapitulo = new dlgNuevoCapitulo(this);
    QMdiSubWindow *window = mdiArea->addSubWindow(dlgCapitulo);
    window->show();
}

void MainWindow::cargarModelos(){

    statusBar()->showMessage("Cargando los modelos", STATUSBAR_TIMEOUT);

    m_temas = TemasModel::InstanceModel();
    // esto no habría que ponerlo en el constructor de la clase?
    m_temas->setSort(1, Qt::AscendingOrder);
    m_temas->select();

    m_lugares = LugaresModel::InstanceModel();
    m_lugares->setSort(1, Qt::AscendingOrder);
    m_lugares->select();

    m_personas = PersonasModel::InstanceModel();
    m_personas->setSort(1, Qt::AscendingOrder);
    m_personas->select();

    m_casas = CasasModel::InstanceModel();
    m_casas->setSort(1, Qt::AscendingOrder);
    m_casas->select();

    m_provincias = ProvinciasModel::InstanceModel();
    m_provincias->setSort(1, Qt::AscendingOrder);
    m_provincias->select();

    m_capitulos = CapitulosModel::InstanceModel();
    m_capitulos->select();

    statusBar()->showMessage("Modelos cargados", STATUSBAR_TIMEOUT);

}

void MainWindow::nuevaResolucion(){
    dlgResolucion = new dlgNuevaResolucion(0, this);
    connect(dlgResolucion, SIGNAL(abrirDetalles(dlgDetalles*)), this, SLOT(abrirDetalles(dlgDetalles*)));
    QMdiSubWindow *window = mdiArea->addSubWindow(dlgResolucion);
    window->show();
}

void MainWindow::nuevaPersona(){
    dlgPersona = new dlgNuevaPersona(this);
    QMdiSubWindow *window = mdiArea->addSubWindow(dlgPersona);
    window->show();
}

void MainWindow::nuevaCasa(){

    // dlgCasa = new dlgNuevaCasa(this);
    // hay q poner this o poner ui->mdiArea como parent?
    dlgCasa = new dlgNuevaCasa(this);
    QMdiSubWindow *window = mdiArea->addSubWindow(dlgCasa);
    window->show();
}

void MainWindow::nuevaDiocesis(){
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

void MainWindow::Capitulos(){
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
    FormCasas = new dlgCasas(this);
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

void MainWindow::nuevaObra(){

    dlgNuevaObra *nuevaObra = new dlgNuevaObra(this);
    QMdiSubWindow *window = mdiArea->addSubWindow(nuevaObra);
    window->show();
}

void MainWindow::nuevaProvincia(){
    dlgNuevaProvincia *dlgprovincia = new dlgNuevaProvincia(this);
    dlgprovincia->show();
}

void MainWindow::nuevoTema(){

    Tema *tema = new Tema();

    QString tematitulo = QInputDialog::getText(this, "Introduzca nuevo tema", "Nueva tema");

    if (!tematitulo.isEmpty()){
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

void MainWindow::on_actionObispos_triggered()
{
    FormObispos = new dlgObispos(this);
    QMdiSubWindow *window = mdiArea->addSubWindow(FormObispos);
    window->show();

    connect(FormObispos, SIGNAL(infoBarraInferior(QString)), this, SLOT(updateStatusBarDerecha(QString)));

    FormObispos->contarTotal();
}

void MainWindow::updateStatusBarDerecha(QString mensaje)
{
    info_statusbar->setText(mensaje);
}
