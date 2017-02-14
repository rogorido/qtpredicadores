#include "nuevocapitulo.h"
#include "ui_nuevocapitulo.h"

#include <QSqlQueryModel>
#include <QCompleter>

/*
#include <QSqlRecord>
#include <QSqlQuery>
*/

NuevoCapitulo::NuevoCapitulo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevoCapitulo)
{
    ui->setupUi(this);

    connect(ui->btCancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarCapitulo()));

    ui->dtFinal->calendarPopup();

    ui->cboTipoCapitulo->addItem("General");
    ui->cboTipoCapitulo->addItem("Provincial");

    cargarCompleters();
}

NuevoCapitulo::~NuevoCapitulo()
{
    delete ui;
}

void NuevoCapitulo::aceptarCapitulo(){

}

void NuevoCapitulo::cargarCompleters(){

    lugar_query = new QSqlQueryModel(this);
    lugar_query->setQuery("SELECT DISTINCT lugar FROM lugares WHERE lugar IS NOT NULL ORDER BY lugar");

    lugar_completer = new QCompleter(this);
    lugar_completer->setModel(lugar_query);
    lugar_completer->setCompletionColumn(0);
    lugar_completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->txtLugar->setCompleter(lugar_completer);

}
