#ifndef QJSONMODEL_H
#define QJSONMODEL_H

#include <QAbstractItemModel>
#include <QJsonDocument>
#include <QJsonObject>

#include "objs/qjsontreeitem.h"

class QJsonModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit QJsonModel(QObject *parent = 0);

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void anadirJson(QJsonObject json);
    QJsonObject getJsonObject(int i);

    QString getJsonString(int i);

    /*
     * esto crea un QString uniendo todos los QJsonObjects
     * No entiendo cómo no existe un método para esto...
     */
    QString getJsonStringTotal();

    void borrarJson(int ordinal);
    void setIdDetails(QList<int> lista_ids);

    void resetearModelo();
    void clear();
    int getSize();

private:
    QJsonTreeItem *mRootItem;
    QJsonDocument mDocument;
    QStringList mHeaders;

    QList<QJsonObject> lista_jsons;

    /*
     * aqui guardamos una lista de ints donde están metidos
     * las ids de la tabla resolutions_details, para cuando se usa
     * con el form de gestión de resoluciones. Es decir, el orden de la lista
     * se corresponde con el de la view y permite borrar/editar
     * los corresondientes QJsonObjects
     */
    QList<int> lista_iddetails;

    /*
     * No sé por qué esto hay que declararlo como const, sino me da un error del tipo
     * passing xxx as 'this' argument of xxx discards qualifiers
     */
    QString sacarLugar(const int lugar_id) const;
    QString sacarCasa(const int lugar_id) const;
    QString sacarProvincia(const int lugar_id) const;
    QString sacarFuente(const int fuente) const;

};

#endif // QJSONMODEL_H
