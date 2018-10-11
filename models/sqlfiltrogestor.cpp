#include "sqlfiltrogestor.h"

#include <QDebug>

SqlFiltroGestor::SqlFiltroGestor(QString sql, QObject *parent) : QObject(parent),
    sql_basico(sql)
{

}

void SqlFiltroGestor::setSqlGeneral(QString sql)
{
    sql_basico = sql;
}

void SqlFiltroGestor::setSqlOrder(QString sql)
{
    sql_order = sql;
}

void SqlFiltroGestor::anadirFiltro(QString nombre, QString sql)
{
    filtros_map.insert(nombre, sql);
    generarSql();
}

void SqlFiltroGestor::quitarFiltro(QString nombre)
{
    filtros_map.remove(nombre);
    qDebug() << "quitado el filtro: " << nombre;
    generarSql();
}

void SqlFiltroGestor::borrarFiltros()
{
    filtros_map.clear();

    emit(actualizadoSqlFiltroGestor(sql_basico));
}

void SqlFiltroGestor::generarSql()
{
    QString filtros_tmp;

    // metemos primero lo básico...
    sql_creado = sql_basico;

    /*
     * en algunos casos puede que sin borrarlos explícitamente
     * al final no haya filtros, por eso lo comprobamos.
     */
    if (filtros_map.size() == 0){
        emit(actualizadoSqlFiltroGestor(sql_creado));
        return;
    }

    QMapIterator<QString, QString> i(filtros_map);
    while (i.hasNext()) {
        i.next();
        filtros_tmp += " AND ";
        filtros_tmp += i.value();
    }

    // tenemos que quitar el primer AND...
    // esto deja el espacio
    filtros_tmp = filtros_tmp.remove(0,4);
    filtros_tmp = " WHERE " + filtros_tmp;

    sql_creado += filtros_tmp;

    qDebug() << "el sql es: " << sql_creado;
    emit(actualizadoSqlFiltroGestor(sql_creado));

}
