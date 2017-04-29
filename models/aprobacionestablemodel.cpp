#include "aprobacionestablemodel.h"

AprobacionesTableModel::AprobacionesTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int AprobacionesTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return listaaprobaciones.size();
}

int AprobacionesTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 2;
}

QVariant AprobacionesTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

QList<Aprobacion> AprobacionesTableModel::getLista()
{
    return listaaprobaciones;
}

void AprobacionesTableModel::anadirAprobacion(Aprobacion aprobracion)
{
    listaaprobaciones.append(aprobracion);

    //emitdataChanged(QModelIndex idx, QModelIndex idx2));
}
