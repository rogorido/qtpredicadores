#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <QTableView>
#include <QDebug>
/*
#include <QSqlRelationalTableModel>
#include <QSortFilterProxyModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QtGui>
#include <QMessageBox>
#include <QInputDialog>

#include <QLabel>

*/

#include "nuevocapitulo.h"

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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::nuevoCapitulo(){
    // probando

    Capitulo = new NuevoCapitulo(this);

    Capitulo->show();
    //Capitulo->activateWindow();
}

void MainWindow::cargarConexiones(){
    connect(ui->btNuevoCapitulo, SIGNAL(clicked()), this, SLOT(nuevoCapitulo()));
}
