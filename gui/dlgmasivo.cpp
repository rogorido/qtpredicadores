#include "dlgmasivo.h"
#include "ui_dlgmasivo.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>

dlgMasivo::dlgMasivo(JsonGestor *json, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgMasivo), jsondetalles(json)
{
    ui->setupUi(this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));

    desmarcarTodasProvincias();
    cargarModelos();
}

dlgMasivo::~dlgMasivo()
{
    delete ui;
}

void dlgMasivo::aceptar()
{

}

void dlgMasivo::desmarcarTodasProvincias()
{
    /*
     * con esto desmacamos todas las provincias que
     * pudieran estar marcadas al principio.
     */

    QSqlQuery query;

    query.exec("UPDATE provinces SET selected=FALSE");

}

void dlgMasivo::cargarModelos()
{


}
