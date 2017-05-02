#include "afiliacionestablemodel.h"

AfiliacionesTableModel::AfiliacionesTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int AfiliacionesTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int AfiliacionesTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant AfiliacionesTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
