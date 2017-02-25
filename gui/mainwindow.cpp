#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QDebug>
#include <QSqlTableModel>

#include "dlgnuevocapitulo.h"
#include "dlgnuevaresolucion.h"
#include "dlgnuevapersona.h"
#include "dlgnuevacasa.h"
#include "models/temasmodel.h"
#include "models/lugaresmodel.h"
#include "models/personasmodel.h"
#include "models/casasmodel.h"
#include "dlgcapitulos.h"
#include "dlgnuevaobra.h"

const int STATUSBAR_TIMEOUT = 1000;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QPSQL");
     db.setHostName("localhost");
     db.setDatabaseName("dominicos");
     db.setUserName("igor");

     if (db.open())
         qDebug() << "Abierta";

     cargarConexiones();
     cargarModelos();
     cargarMenues();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargarMenues(){
    connect(ui->actionNuevoCapitulo, SIGNAL(triggered()), this, SLOT(nuevoCapitulo()));
    connect(ui->actionCapitulos, SIGNAL(triggered()), this, SLOT(Capitulos()));
    connect(ui->actionNuevaCasa, SIGNAL(triggered()), this, SLOT(nuevaCasa()));
    connect(ui->actionNuevaPersona, SIGNAL(triggered()), this, SLOT(nuevaPersona()));
    connect(ui->actionNuevaObra, SIGNAL(triggered()), this, SLOT(nuevaObra()));
    connect(ui->actionSalir, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::nuevoCapitulo(){

    dlgCapitulo = new dlgNuevoCapitulo(this);

    dlgCapitulo->show();
    //Capitulo->activateWindow();
}

void MainWindow::cargarConexiones(){
    connect(ui->btNuevoCapitulo, SIGNAL(clicked()), this, SLOT(nuevoCapitulo()));
    connect(ui->btNuevaResolucion, SIGNAL(clicked(bool)), this, SLOT(nuevaResolucion()));
    connect(ui->btPersona, SIGNAL(clicked()), this, SLOT(nuevaPersona()));
    connect(ui->btNuevaCasa, SIGNAL(clicked()), this, SLOT(nuevaCasa()));

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
    dlgCasa = new dlgNuevaCasa(this);
    dlgCasa->show();
}

void MainWindow::Capitulos(){
    FormCapitulos = new dlgCapitulos(this);
    FormCapitulos->show();
}

void MainWindow::nuevaObra(){

    dlgNuevaObra *nuevaObra = new dlgNuevaObra(this);
    nuevaObra->show();
}
