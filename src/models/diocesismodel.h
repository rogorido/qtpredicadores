#ifndef DIOCESISMODEL_H
#define DIOCESISMODEL_H

#include <QSqlTableModel>

#include "src/objs/diocesis.h"

class DiocesisModel : public QSqlTableModel
{
    Q_OBJECT

public:
    static DiocesisModel *InstanceModel();

    bool AnadirDiocesis(const Diocesis *diocesis, bool nuevadiocesis);
    Diocesis *devolverDiocesis(const int id);
    void actualizarDiocesis(const int id);

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
