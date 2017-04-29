#include "aprobacionestablemodel.h"

AprobacionesTableModel::AprobacionesTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int AprobacionesTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int AprobacionesTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant AprobacionesTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
