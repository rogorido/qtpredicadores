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

    /*
     * hay una función overloaded pq a veces en el QJsonObject metemos
     * el id mientras en el treewidget metemos pej el nombre de la ciudad
     */
    void anadirValor(const QString &key, const QJsonValue &value);
    void anadirValor(const QString &key, const QString &value, int id);

    void nuevoBloqueJson();
    /*
     * esto es una tontería que habría que hacerlo de otra forma
     * pero consiste en que meta el último m_json_activo en la lista
     * general antes de pasar a introducir los datos en la bd
     */
    void actualizarPrevioIntroducir();

    int getSize();

    QString getJsonString(int i);

private:

    QTreeWidget *tree_original;
    QTreeWidgetItem *item_activo;

    QJsonObject m_json_activo;
    QList<QJsonObject> m_json_general;

    void anadirChildItem(const QString &key, const QString &value);
};

#endif // JSONGESTOR_H
