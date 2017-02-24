#ifndef JSONGESTOR_H
#define JSONGESTOR_H

#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>

class QTreeWidget;
class QTreeWidgetItem;

class JsonGestor
{
public:
    JsonGestor(QTreeWidget *tree);

    void anadirValor(const QString &key, const QJsonValue &value);
    void setTreeView(QTreeWidget * tree);

private:

    QTreeWidget *tree_original;
    QTreeWidgetItem *item_activo;

    QJsonObject m_json_activo;
    QList<QJsonObject> m_json_general;
};

#endif // JSONGESTOR_H
