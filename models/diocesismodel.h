#ifndef DIOCESISMODEL_H
#define DIOCESISMODEL_H

#include <QSqlTableModel>

class Diocesis;

class DiocesisModel : public QSqlTableModel
{
    Q_OBJECT

public:
    static DiocesisModel *InstanceModel();

    bool AnadirDiocesis(const Diocesis *diocesis);

signals:

    void actualizado();

protected:
    DiocesisModel();
    DiocesisModel(const DiocesisModel &);
    DiocesisModel &operator =(const DiocesisModel &);

private:
    static DiocesisModel *pInstance;
    static void DestroyMe();

};

#endif // DIOCESISMODEL_H
