#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QDebug>
#include <QInputDialog>
#include <QSqlTableModel>
#include <QMdiSubWindow>

#include "dlgnuevocapitulo.h"
#include "dlgnuevaresolucion.h"
#include "dlgnuevapersona.h"
#include "dlgnuevacasa.h"
#include "dlgnuevaobra.h"
#include "dlgnuevaprovincia.h"
#include "dlgnuevadiocesis.h"
#include "dlgnuevoobispo.h"
#include "dlgnuevafuente.h"
#include "dlgresoluciones.h"
#include "dlgciudades.h"
#include "dlgcasas.h"
#include "dlgcapitulos.h"
#include "dlgestadisticas.h"
#include "dlgreforma.h"

#include "models/temasmodel.h"
#include "models/lugaresmodel.h"
#include "models/personasmodel.h"
#include "models/casasmodel.h"
#include "models/provinciasmodel.h"
#include "models/capitulosmodel.h"

#include "objs/tema.h"

const int STATUSBAR_TIMEOUT = 1000;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->mdiArea);
    QMainWindow::showMaximized();

    db = QSqlDatabase::addDatabase("QPSQL");
     db.setHostName("localhost");
     db.setDatabaseName("domis");
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
    connect(ui->actionNuevoCapitulo, SIGNAL(triggered()), this, SLOT(nuevoCapitulo()));
    connect(ui->actionNuevaCasa, SIGNAL(triggered()), this, SLOT(nuevaCasa()));
    connect(ui->actionNuevaPersona, SIGNAL(triggered()), this, SLOT(nuevaPersona()));
    connect(ui->actionNuevaObra, SIGNAL(triggered()), this, SLOT(nuevaObra()));
    connect(ui->actionNuevaProvincia, SIGNAL(triggered()), this, SLOT(nuevaProvincia()));
    connect(ui->actionNuevaDiocesis, SIGNAL(triggered()), this, SLOT(nuevaDiocesis()));
    connect(ui->actionNuevoTema, SIGNAL(triggered()), this, SLOT(nuevoTema()));
    connect(ui->actionNuevaResolucion, SIGNAL(triggered(bool)), this, SLOT(nuevaResolucion()));
    connect(ui->actionNuevoObispo, SIGNAL(triggered(bool)), this, SLOT(nuevoObispo()));
    connect(ui->actionNuevaFuente, SIGNAL(triggered(bool)), this, SLOT(nuevaFuente()));
    connect(ui->actionIntroducirReformaConvento, SIGNAL(triggered(bool)), this, SLOT(nuevaReforma()));
    connect(ui->actionResoluciones, SIGNAL(triggered(bool)), this, SLOT(Resoluciones()));
    connect(ui->actionCiudades, SIGNAL(triggered(bool)), this, SLOT(Ciudades()));
    connect(ui->actionCasas, SIGNAL(triggered(bool)), this, SLOT(Casas()));
    connect(ui->actionCapituli, SIGNAL(triggered(bool)), this, SLOT(Capitulos()));
    connect(ui->actionGeneralEstadisticas, SIGNAL(triggered(bool)), this, SLOT(Estadisticas()));
    connect(ui->actionSalir, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::nuevoCapitulo(){

    dlgCapitulo = new dlgNuevoCapitulo(this);
    dlgCapitulo->show();
}

void MainWindow::cargarModelos(){

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

}

void MainWindow::nuevaResolucion(){
    dlgResolucion = new dlgNuevaResolucion(0, this);
    dlgResolucion->show();
}

void MainWindow::nuevaPersona(){
    dlgPersona = new dlgNuevaPersona(this);
    dlgPersona->show();
}

void MainWindow::nuevaCasa(){

    // dlgCasa = new dlgNuevaCasa(this);
    // hay q poner this o poner ui->mdiArea como parent?
    dlgCasa = new dlgNuevaCasa(ui->mdiArea);
    QMdiSubWindow *window = ui->mdiArea->addSubWindow(dlgCasa);

    window->show();

}

void MainWindow::nuevaDiocesis(){
    dlgDiocesis = new dlgNuevaDiocesis(this);
    dlgDiocesis->show();
}

void MainWindow::nuevoObispo()
{
    dlgObispo = new dlgNuevoObispo(this);
    dlgObispo->show();
}

void MainWindow::Capitulos(){
    FormCapitulos = new dlgCapitulos(this);
    FormCapitulos->show();
}

void MainWindow::Resoluciones()
{
    FormResoluciones = new DlgResoluciones(this);
    FormResoluciones->show();
}

void MainWindow::Ciudades()
{
    FormCiudades = new dlgCiudades(this);
    FormCiudades->show();
}

void MainWindow::Casas()
{
    FormCasas = new dlgCasas(this);
    FormCasas->show();
}

void MainWindow::Estadisticas()
{
    FormEstadisticas = new dlgEstadisticas(this);
    QMdiSubWindow *window = ui->mdiArea->addSubWindow(FormEstadisticas);

    window->show();
}

void MainWindow::nuevaObra(){

    dlgNuevaObra *nuevaObra = new dlgNuevaObra(this);
    nuevaObra->show();
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
