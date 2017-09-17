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

void SqlFiltroGestor::generarSql()
{
    QString filtros_tmp;
    QMap<QString, QString> map;

    // metemos primero lo básico...
    sqlcreado = sqlgeneral;

    QMapIterator<QString, QString> i(map);
    while (i.hasNext()) {
        i.next();
        filtros_tmp += " AND ";
        filtros_tmp += i.value();
    }

    // tenemos que quitar el primer AND...
    // esto deja el espacio
    filtros_tmp = filtros_tmp.right(5);
    filtros_tmp = " WHERE " + filtros_tmp;

    sqlcreado += filtros_tmp;

    emit(actualizadoSqlFiltroGestor(sqlcreado));

}
