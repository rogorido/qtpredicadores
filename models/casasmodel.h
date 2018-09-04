#ifndef CASASMODEL_H
#define CASASMODEL_H

#include <QSqlQueryModel>
#include <QIcon>

class Casa;

class CasasModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    static CasasModel *InstanceModel();
    QVariant data(const QModelIndex &index, int role) const override;

    bool AnadirCasa(const Casa *casa);

signals:

    void actualizado();

protected:
    CasasModel();
    CasasModel(const CasasModel &);
    CasasModel &operator =(const CasasModel &);

private:
    static CasasModel *pInstance;
    static void DestroyMe();    

    QIcon icono_masculino;
    QIcon icono_femenino;

};

#endif // CASASMODEL_H
