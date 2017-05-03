#ifndef QJSONTREEITEM_H
#define QJSONTREEITEM_H

#include <QString>
#include <QJsonValue>
#include <QList>

class QJsonTreeItem
{
public:
    QJsonTreeItem();
    ~QJsonTreeItem();

    QJsonTreeItem *child(int row);
    QJsonTreeItem *parent();

    void setKey(const QString& key);
    void setValue(const QString& value);
    void setType(const QJsonValue::Type& type);

    void appendChild(QJsonTreeItem * item);

    // getters
    QString key() const;
    QString value() const;
    QJsonValue::Type type() const;

    int childCount() const;
    int row() const;

    static QJsonTreeItem* load(const QJsonValue& value, QJsonTreeItem * parent = 0);

protected:

private:

    QString mKey;
    QString mValue;
    QJsonValue::Type mType;
    QList<QJsonTreeItem*> mChilds;
    QJsonTreeItem * mParent;

};

#endif // QJSONTREEITEM_H
