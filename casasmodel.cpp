#include "casasmodel.h"

#include <QSqlQuery>

CasasModel::CasasModel(QObject *parent) :
    QSqlTableModel(parent)
{
    this->setTable("casas");

}

void CasasModel::AnadirCasa(const QString casa){
    QSqlQuery query;

    query.prepare("INSERT INTO casas(nombre) VALUES(:casa)");
    query.bindValue(":casa", casa);
    query.exec();

    this->select();
}
