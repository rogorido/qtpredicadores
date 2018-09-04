#include "qjsonmodel.h"

#include <QDebug>
#include <QSqlQuery>

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
    QString valor;

    if (!index.isValid())
            return QVariant();

    QJsonTreeItem *item = static_cast<QJsonTreeItem*>(index.internalPointer());

    if (role == Qt::DisplayRole) {
        if (index.column() == 0)  {
            return QString("%1").arg(item->getKey());
        }

        if (index.column() == 1) {
            if (item->getKey() == "lugar" or item->getKey() == "viaje_origen" or item->getKey() == "viaje_destino") {
                valor = sacarLugar(item->getValue().toInt());
                return valor;
            }
            else if (item->getKey() == "casa") {
                valor = sacarCasa(item->getValue().toInt());
                return valor;
            }
            else if (item->getKey() == "provincia") {
                valor = sacarProvincia(item->getValue().toInt());
                return valor;
            }
            else if (item->getKey() == "source_id") {
                valor = sacarFuente(item->getValue().toInt());
                return valor;
            }
            else
                return QString("%1").arg(item->getValue());
        }
        }

    return QVariant();
}

void QJsonModel::anadirJson(QJsonObject json)
{
    lista_jsons.append(json);
}

QJsonObject QJsonModel::getJsonObject(int i)
{
    return lista_jsons.at(i);
}

int QJsonModel::getSize()
{
    return lista_jsons.size();
}

QString QJsonModel::sacarLugar(const int lugar_id) const
{
    QSqlQuery query;
    QString sql;

    sql = QString("SELECT * FROM places where place_id = %1").arg(lugar_id);

    if (query.exec(sql)) {
        query.first();
        return query.value(1).toString();
    }
    else
        return "";
}

QString QJsonModel::sacarCasa(const int lugar_id) const
{
    QSqlQuery query;
    QString sql;

    sql = QString("SELECT * FROM houses where house_id = %1").arg(lugar_id);

    if (query.exec(sql)) {
        query.first();
        return query.value(1).toString();
    }
    else
        return "";
}

QString QJsonModel::sacarProvincia(const int lugar_id) const
{
    QSqlQuery query;
    QString sql;

    sql = QString("SELECT * FROM provinces where province_id = %1").arg(lugar_id);

    if (query.exec(sql)) {
        query.first();
        return query.value(1).toString();
    }
    else
        return "";
}

QString QJsonModel::sacarFuente(const int fuente) const
{
    QSqlQuery query;
    QString sql;

    sql = QString("SELECT * FROM sources WHERE source_id = %1 ").arg(fuente);

    if (query.exec(sql)) {
        query.first();
        return query.value(1).toString();
    }
    else
        return "";
}

void QJsonModel::clear()
{
    lista_jsons.clear();
    resetearModelo();
}

QString QJsonModel::getJsonString(int i)
{
    QJsonDocument jsondoc(lista_jsons.at(i));
    QString jsonfinal;

    jsonfinal = jsondoc.toJson(QJsonDocument::Compact);

    return jsonfinal;
}

QString QJsonModel::getJsonStringTotal()
{
    QString final;

    for (int i = 0; i < lista_jsons.size(); ++i) {
        QString transformado = getJsonString(i);
        transformado.remove(0,1); // quitamos el primer {
        transformado.chop(1); // y el último
        final = final + QString(", ") + transformado;
    }

    // quitamos el primer " ," que queda de crear la string
    final.remove(0,2);
    final = QString("{") + final + QString("}");

    return final;

}

void QJsonModel::borrarJson(int ordinal)
{
    lista_jsons.removeAt(ordinal);
    resetearModelo();
}

void QJsonModel::setIdDetails(QList<int> lista_ids)
{
    lista_iddetails = lista_ids;
}

void QJsonModel::resetearModelo()
{
    QJsonObject general;

    beginResetModel();

    for (int i = 0; i < lista_jsons.size(); ++i) {
        QString llave = "Datos-" + QString::number(i);
        general.insert(llave, lista_jsons.at(i));
    }

    mRootItem = QJsonTreeItem::load(general);

    endResetModel();
}
