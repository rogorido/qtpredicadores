#include "casas.h"

#include <QSqlQuery>

Casas::Casas(QObject *parent) :
    QSqlTableModel(parent)
{
    this->setTable("casas");

}

void Casas::AnadirCasa(const QString casa){
    QSqlQuery query;

    query.prepare("INSERT INTO casas(nombre) VALUES(:casa)");
    query.bindValue(":casa", casa);
    query.exec();

    this->select();
}
