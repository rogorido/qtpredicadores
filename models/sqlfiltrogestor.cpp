#include "sqlfiltrogestor.h"

SqlFiltroGestor::SqlFiltroGestor(QString sql, QObject *parent) : QObject(parent),
    sqlgeneral(sql)
{

}

void SqlFiltroGestor::setSqlGeneral(QString sql)
{
    sqlgeneral = sql;
}

void SqlFiltroGestor::setSqlOrder(QString sql)
{
    sqlorder = sql;
}

void SqlFiltroGestor::anadirFiltro(QString nombre, QString sql)
{
    filtros.insert(nombre, sql);
}

void SqlFiltroGestor::quitarFiltro(QString nombre)
{
    filtros.remove(nombre);
}

void SqlFiltroGestor::borrarFiltros()
{
    filtros.clear();
}
