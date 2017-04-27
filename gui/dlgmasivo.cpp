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

    desmarcarTodasProvincias();
}

dlgMasivo::~dlgMasivo()
{
    delete ui;
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
