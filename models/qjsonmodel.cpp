#include "qjsonmodel.h"

QJsonModel::QJsonModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QModelIndex QJsonModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex QJsonModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int QJsonModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int QJsonModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant QJsonModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
