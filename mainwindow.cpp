#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QSqlTableModel>

#include "nuevocapitulo.h"
#include "nuevaresolucion.h"
#include "nuevapersona.h"
#include "temasmodel.h"
#include "lugares.h"
#include "personas.h"
#include "casasmodel.h"

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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::nuevoCapitulo(){

    Capitulo = new NuevoCapitulo(m_lugares, this);

    Capitulo->show();
    //Capitulo->activateWindow();
}

void MainWindow::cargarConexiones(){
    connect(ui->btNuevoCapitulo, SIGNAL(clicked()), this, SLOT(nuevoCapitulo()));
    connect(ui->btNuevaResolucion, SIGNAL(clicked(bool)), this, SLOT(nuevaResolucion()));
    connect(ui->btPersona, SIGNAL(clicked()), this, SLOT(nuevaPersona()));

}

void MainWindow::cargarModelos(){

    m_temas = new TemasModel(this);
    // esto no habría que ponerlo en el constructor de la clase?
    m_temas->setSort(1, Qt::AscendingOrder);
    m_temas->select();

    m_lugares = new Lugares(this);
    m_lugares->setSort(1, Qt::AscendingOrder);
    m_lugares->select();

    m_personas = new Personas(this);
    m_personas->setSort(1, Qt::AscendingOrder);
    m_personas->select();

    m_casas = new CasasModel(this);
    m_casas->setSort(1, Qt::AscendingOrder);
    m_casas->select();
}

void MainWindow::nuevaResolucion(){

    Resolucion = new NuevaResolucion(m_temas, m_lugares, m_personas, m_casas, this);

    Resolucion->show();

}

void MainWindow::nuevaPersona(){
    Persona = new NuevaPersona(m_personas, this);

    Persona->show();
}

