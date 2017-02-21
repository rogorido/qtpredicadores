#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QDebug>
#include <QSqlTableModel>

#include "nuevocapitulo.h"
#include "nuevaresolucion.h"
#include "nuevapersona.h"
#include "nuevacasa.h"
#include "temasmodel.h"
#include "lugaresmodel.h"
#include "personasmodel.h"
#include "casasmodel.h"
#include "dlgcapitulos.h"

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
    connect(ui->actionSalir, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::nuevoCapitulo(){

    Capitulo = new NuevoCapitulo(this);

    Capitulo->show();
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

    m_personas = new PersonasModel(this);
    m_personas->setSort(1, Qt::AscendingOrder);
    m_personas->select();

    m_casas = new CasasModel(this);
    m_casas->setSort(1, Qt::AscendingOrder);
    m_casas->select();
}

void MainWindow::nuevaResolucion(){

    Resolucion = new NuevaResolucion(m_personas, m_casas, 0, this);

    Resolucion->show();

}

void MainWindow::nuevaPersona(){
    Persona = new NuevaPersona(m_personas, this);

    Persona->show();
}

void MainWindow::nuevaCasa(){
    Casa = new NuevaCasa(m_casas, m_lugares, this);

    Casa->show();
}

void MainWindow::Capitulos(){
    FormCapitulos = new DlgCapitulos(this);

    FormCapitulos->show();
}
