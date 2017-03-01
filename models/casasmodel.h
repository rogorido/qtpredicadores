#ifndef CASASMODEL_H
#define CASASMODEL_H

#include <QSqlTableModel>

class Casa;

class CasasModel : public QSqlTableModel
{
    Q_OBJECT

public:
    static CasasModel *InstanceModel();

    void AnadirCasa(const Casa *casa);

signals:

    void actualizado();

protected:
    CasasModel();
    CasasModel(const CasasModel &);
    CasasModel &operator =(const CasasModel &);

private:
    static CasasModel *pInstance;
    static void DestroyMe();

};

#endif // CASASMODEL_H
