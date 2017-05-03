#include "qjsontreeitem.h"

#include <QDebug>

QJsonTreeItem::QJsonTreeItem(QJsonTreeItem *parent)
{
    mParent = parent;
}

QJsonTreeItem::~QJsonTreeItem()
{
    qDeleteAll(mChilds);
}

QJsonTreeItem *QJsonTreeItem::child(int row)
{
    return mChilds.value(row);
}

QJsonTreeItem *QJsonTreeItem::parent()
{
    return mParent;
}

void QJsonTreeItem::setKey(const QString &key)
{
    mKey = key;
}

void QJsonTreeItem::setValue(const QString &value)
{
    mValue = value;
}

void QJsonTreeItem::setType(const QJsonValue::Type &type)
{
    mType = type;
}

void QJsonTreeItem::appendChild(QJsonTreeItem *item)
{
    mChilds.append(item);
}

int QJsonTreeItem::childCount() const
{
    return mChilds.count();
}

int QJsonTreeItem::row() const
{
    if (mParent)
            return mParent->mChilds.indexOf(const_cast<QJsonTreeItem*>(this));

    return 0;
}

QJsonTreeItem *QJsonTreeItem::load(const QJsonValue &value, QJsonTreeItem *parent)
{
    QJsonTreeItem * rootItem = new QJsonTreeItem(parent);
        rootItem->setKey("root");

        if ( value.isObject())
        {

            //Get all QJsonValue childs
            for (QString key : value.toObject().keys()){
                QJsonValue v = value.toObject().value(key);
                QJsonTreeItem * child = load(v,rootItem);
                child->setKey(key);
                child->setType(v.type());
                rootItem->appendChild(child);

            }

        }

        else if ( value.isArray())
        {
            //Get all QJsonValue childs
            int index = 0;
            for (QJsonValue v : value.toArray()){

                QJsonTreeItem * child = load(v,rootItem);
                child->setKey(QString::number(index));
                child->setType(v.type());
                rootItem->appendChild(child);
                ++index;
            }
        }
        else
        {
            rootItem->setValue(value.toVariant().toString());
            rootItem->setType(value.type());
        }

        return rootItem;
}
