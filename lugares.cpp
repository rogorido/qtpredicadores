#include "lugares.h"

#include <QSqlQuery>

Lugares::Lugares(QObject *parent) :
    QSqlTableModel(parent)
{
    this->setTable("lugares");

}

void Lugares::AnadirLugar(const QString lugar){
    QSqlQuery query;

    query.prepare("INSERT INTO lugares(lugar) VALUES(:lugar)");
    query.bindValue(":lugar", lugar);
    query.exec();

    this->select();
}
