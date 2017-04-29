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

    if (index.row() >= listaaprobaciones.size() || index.row() < 0)
            return QVariant();

    if (role == Qt::DisplayRole) {
            Aprobacion *aprobacion = listaaprobaciones.at(index.row());

            if (index.column() == 0)
                return aprobacion->getPersona().getNombre();
            else if (index.column() == 1)
                return aprobacion->getProvincia().getNombre();
        }

    return QVariant();
}

QList<Aprobacion*> AprobacionesTableModel::getLista()
{
    return listaaprobaciones;
}

void AprobacionesTableModel::anadirAprobacion(Aprobacion *aprobracion)
{
    /*
     * esto así creo que es una chapuza
     */
    beginResetModel();
    listaaprobaciones.append(aprobracion);
    endResetModel();
    //emitdataChanged(QModelIndex idx, QModelIndex idx2));
}
