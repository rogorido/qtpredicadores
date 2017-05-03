#include "qjsonmodel.h"

#include <QDebug>

QJsonModel::QJsonModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    mRootItem = new QJsonTreeItem();
    mHeaders.append("key");
    mHeaders.append("value");
}

QModelIndex QJsonModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
            return QModelIndex();

    QJsonTreeItem *parentItem;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<QJsonTreeItem*>(parent.internalPointer());

    QJsonTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex QJsonModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
            return QModelIndex();

    QJsonTreeItem *childItem = static_cast<QJsonTreeItem*>(index.internalPointer());
    QJsonTreeItem *parentItem = childItem->parent();

    if (parentItem == mRootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

QVariant QJsonModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
            return QVariant();

    if (orientation == Qt::Horizontal) {
            return mHeaders.value(section);
        }
    else
        return QVariant();

}

int QJsonModel::rowCount(const QModelIndex &parent) const
{
    QJsonTreeItem *parentItem;

    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<QJsonTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int QJsonModel::columnCount(const QModelIndex &parent) const
{

    return 2;
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

void QJsonModel::anadirJson(QJsonObject json)
{
    QJsonObject general;

    beginResetModel();

    lista_jsons.append(json);

    for (int i = 0; i < lista_jsons.size(); ++i) {
        QString llave = "Datos-" + QString::number(i);
        general.insert(llave, lista_jsons.at(i));
    }

    mRootItem = QJsonTreeItem::load(general);

    endResetModel();
}
