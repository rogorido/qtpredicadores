#include "temas.h"

#include <QSqlQuery>

Temas::Temas(QObject *parent) :
    QSqlTableModel(parent)
{
    this->setTable("temas");
}

void Temas::AnadirTema(const QString tema){
    QSqlQuery query;

    query.prepare("INSERT INTO temas(tema) VALUES(:tema)");
    query.bindValue(":tema", tema);
    query.exec();

    this->select();
}
