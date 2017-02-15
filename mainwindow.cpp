#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <QTableView>
#include <QDebug>
#include <QSqlTableModel>
/*
#include <QSqlRelationalTableModel>
#include <QSortFilterProxyModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QtGui>
#include <QMessageBox>
#include <QInputDialog>

#include <QLabel>

*/

#include "nuevocapitulo.h"
#include "nuevaresolucion.h"
#include "temas.h"
#include "lugares.h"

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

}

void MainWindow::cargarModelos(){

    m_temas = new Temas(this);
    // esto no habría que ponerlo en el constructor de la clase?
    m_temas->setSort(1, Qt::AscendingOrder);
    m_temas->select();

    m_lugares = new Lugares(this);
    m_lugares->setSort(1, Qt::AscendingOrder);
    m_lugares->select();
}

void MainWindow::nuevaResolucion(){

    Resolucion = new NuevaResolucion(m_temas, m_lugares, this);

    Resolucion->show();

}
