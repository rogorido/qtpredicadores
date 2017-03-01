#ifndef LUGARESMODEL_H
#define LUGARESMODEL_H

#include <QSqlTableModel>

class LugaresModel : public QSqlTableModel
{
    Q_OBJECT

public:
    static LugaresModel *InstanceModel();

    /*
     * lo hacemos overload pq si no me mete un {} en el json
     * cuando está vacío y no quiero tenerlo así... pero tiene que haber
     * otra forma mejor que esto así...
     */
    void AnadirLugar(const QString &lugar, const QString &pais);
    void AnadirLugar(const QString &lugar, const QString &pais, const QString &otrosnombres);

signals:

    void actualizado();

protected:
    LugaresModel();
    LugaresModel(const LugaresModel &);
    LugaresModel &operator=(const LugaresModel &);

private:
    static LugaresModel *pInstance;
    static void DestroyMe();
};

#endif // LUGARESMODEL_H
