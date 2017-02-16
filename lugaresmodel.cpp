#include "lugares.h"

#include <QSqlQuery>

Lugares::Lugares(QObject *parent) :
    QSqlTableModel(parent)
{
    this->setTable("lugares");
}

void Lugares::AnadirLugar(const QString lugar){

    /*
     * TODO: habría que comprobar que siemrpe hay país...
     */
    QSqlQuery query;
    QStringList campos = lugar.split(',');

    query.prepare("INSERT INTO lugares(lugar, pais) VALUES(:lugar, :pais)");
    query.bindValue(":lugar", campos[0]);
    query.bindValue(":pais", campos[1]);
    query.exec();

    this->select();
}
