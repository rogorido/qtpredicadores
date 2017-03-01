#ifndef LUGARESMODEL_H
#define LUGARESMODEL_H

#include <QSqlTableModel>

class LugaresModel : public QSqlTableModel
{
    Q_OBJECT

public:
    static LugaresModel *InstanceModel();

    void AnadirLugar(const QString &lugar, const QString &pais, const QString &otrosnombres);

protected:
    LugaresModel();
    LugaresModel(const LugaresModel &);
    LugaresModel &operator=(const LugaresModel &);

private:
    static LugaresModel *pInstance;
    static void DestroyMe();
};

#endif // LUGARESMODEL_H
