#ifndef OBRASMODEL_H
#define OBRASMODEL_H

#include <QSqlTableModel>

class Obra;

class CasasModel : public QSqlTableModel
{
    Q_OBJECT

public:
    static ObrasModel *InstanceModel();

    void AnadirCasa(const Obra *obra);

protected:
    ObrasModel();
    ObrasModel(const ObrasModel &);
    ObrasModel &operator =(const ObrasModel &);

private:
    static ObrasModel *pInstance;
    static void DestroyMe();

};

#endif // OBRASMODEL_H
