#include "temasmodel.h"

#include <QSqlQuery>

TemasModel::TemasModel(QObject *parent) :
    QSqlTableModel(parent)
{
    this->setTable("temas");
}

void TemasModel::AnadirTema(const QString tema){
    QSqlQuery query;

    query.prepare("INSERT INTO temas(tema) VALUES(:tema)");
    query.bindValue(":tema", tema);
    query.exec();

    this->select();
}
