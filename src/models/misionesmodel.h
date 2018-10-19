#ifndef MISIONESMODEL_H
#define MISIONESMODEL_H

#include <QSqlTableModel>

class Mision;

class MisionesModel : public QSqlTableModel
{
    Q_OBJECT

public:
    static MisionesModel *InstanceModel();

    bool AnadirMision(const Mision *mision);

signals:

    void actualizado();

protected:
    MisionesModel();
    MisionesModel(const MisionesModel &);
    MisionesModel &operator =(const MisionesModel &);

private:
    static MisionesModel *pInstance;
    static void DestroyMe();

};

#endif // MISIONESMODEL_H
