#include "personas.h"

#include <QSqlQuery>

Personas::Personas(QObject *parent) :
    QSqlTableModel(parent)
{
    this->setTable("personas");

}

void Personas::AnadirPersona(const QString persona){
    QSqlQuery query;

    query.prepare("INSERT INTO persona(nombre) VALUES(:persona)");
    query.bindValue(":persona", persona);
    query.exec();

    this->select();
}
