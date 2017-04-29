#ifndef JSONGESTOR_H
#define JSONGESTOR_H

#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>
#include <QVector>

class QTreeWidget;
class QTreeWidgetItem;

class JsonGestor : public QObject
{

    Q_OBJECT

public:
    JsonGestor(QObject *parent = 0);

    void setTreeWidget(QTreeWidget *tree);
    void crearItemRootGeneral();

    /*
     * hay una función overloaded pq a veces en el QJsonObject metemos
     * el id mientras en el treewidget metemos pej el nombre de la ciudad
     */
    void anadirValor(const QString &key, const QJsonValue &value);
    void anadirValor(const QString &key, const QString &value, int id);

    void anadirItemNivelCero();

    /*
     * esto es una tontería que habría que hacerlo de otra forma
     * pero consiste en que meta el último m_json_activo en la lista
     * general antes de pasar a introducir los datos en la bd
     */
    void actualizarPrevioIntroducir();

    int getSize();
    bool isEmpty();

    QString getJsonString(int i);

public slots:

    void modificandoDatos(bool checked);
    void nuevoBloqueJson();
    void eliminarElemento();

private:

    QTreeWidget *tree_original;
    QTreeWidgetItem *item_activo;

    QJsonObject m_json_activo;
    QVector<QJsonObject> m_json_general;

    /*
     * estas variables sirven para controlar si vamos a meter
     * datos nuevos o a modificar existentes. Es una cutrada, pero
     * por ahora no se me ocurre nada mejor..
     */
    bool modificando;
    int posicion;

    /*
     * esta variable sirve para bloquear la entrada cuando hemos
     * borrado algo. La verdad es que es una chapuza. La razón es que al
     * borrar deja de haber un m_json_activo y un item_activo claro.
     * Pero esto es la clave de todo la clase y habría que pensarlo mejor.
     * Al añadir un nuevo bloque se desbloquea...
     */
    bool bloqueadaEntrada;

    void anadirChildItem(const QString &key, const QString &value);
};

#endif // JSONGESTOR_H
