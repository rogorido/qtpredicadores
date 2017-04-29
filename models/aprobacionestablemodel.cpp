#include "aprobacionestablemodel.h"

AprobacionesTableModel::AprobacionesTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant AprobacionesTableModel::headerData(int section, Qt::Orientation orientation, int role) const{

    if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return tr("Persona");

                case 1:
                    return tr("Provincia");

                default:
                    return QVariant();
            }
        }
        return QVariant();
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
            QString persona = aprobacion->getPersona().getNombre() + ' ' + aprobacion->getPersona().getApellidos();

            if (index.column() == 0)
                return persona;
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

void AprobacionesTableModel::quitarAprobacion(int row)
{
    /*
     * esto así creo que es una chapuza
     */
    beginResetModel();
    removeRow(row);
    endResetModel();

    listaaprobaciones.removeAt(row);
}
