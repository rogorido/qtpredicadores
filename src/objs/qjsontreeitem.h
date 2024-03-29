#ifndef QJSONTREEITEM_H
#define QJSONTREEITEM_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>
#include <QString>

class QJsonTreeItem {
 public:
  QJsonTreeItem(QJsonTreeItem* parent = 0);
  ~QJsonTreeItem();

  QJsonTreeItem* child(int row);
  QJsonTreeItem* parent();

  void setKey(const QString& key);
  void setValue(const QString& value);
  void setType(const QJsonValue::Type& type);

  void appendChild(QJsonTreeItem* item);

  // getters
  QString getKey() const { return mKey; }
  QString getValue() const { return mValue; }
  QJsonValue::Type getType() const { return mType; }

  int childCount() const;
  int row() const;

  static QJsonTreeItem* load(const QJsonValue& value,
                             QJsonTreeItem* parent = 0);

 protected:
 private:
  QString mKey;
  QString mValue;
  QJsonValue::Type mType;
  QList<QJsonTreeItem*> mChilds;
  QJsonTreeItem* mParent;
};

#endif  // QJSONTREEITEM_H
