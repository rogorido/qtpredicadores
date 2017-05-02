#include "afiliacionestablemodel.h"

AfiliacionesTableModel::AfiliacionesTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int AfiliacionesTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    lista_afiliaciones.size();
}

int AfiliacionesTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 6;
}

QVariant AfiliacionesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return tr("Persona");
                case 1:
                    return tr("Casa de origen");
                case 2:
                    return tr("Casa de destino");
                case 3:
                    return tr("Provincia de origen");
                case 4:
                    return tr("Provincia de destino");
                case 5:
                    return tr("Extras");
                default:
                    return QVariant();
            }
        }
        return QVariant();
}

QVariant AfiliacionesTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

QList<Afiliacion *> AfiliacionesTableModel::getLista()
{
    return lista_afiliaciones;
}

void AfiliacionesTableModel::anadirAfiliacion(Afiliacion *afiliacion)
{
    /*
     * esto así creo que es una chapuza
     */
    beginResetModel();
    lista_afiliaciones.append(afiliacion);
    endResetModel();
}

void AfiliacionesTableModel::quitarAfiliacion(int row)
{
    /*
     * esto así creo que es una chapuza
     */
    beginResetModel();
    removeRow(row);
    endResetModel();

    lista_afiliaciones.removeAt(row);
}
