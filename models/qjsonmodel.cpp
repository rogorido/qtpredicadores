#include "qjsonmodel.h"

QJsonModel::QJsonModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    mRootItem = new QJsonTreeItem();
    mHeaders.append("key");
    mHeaders.append("value");
}

QModelIndex QJsonModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex QJsonModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

QVariant QJsonModel::headerData(int section, Qt::Orientation orientation, int role) const
{

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

    QJsonTreeItem *item = static_cast<QJsonTreeItem*>(index.internalPointer());

    if (role == Qt::DisplayRole) {
        if (index.column() == 0)
            return QString("%1").arg(item->getKey());

            if (index.column() == 1)
                return QString("%1").arg(item->getValue());
        }

    return QVariant();
}
