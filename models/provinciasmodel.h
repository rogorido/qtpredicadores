#ifndef PROVINCIASMODEL_H
#define PROVINCIASMODEL_H

#include <QSqlTableModel>

class Provincia;

class ProvinciasModel : public QSqlTableModel
{
    Q_OBJECT

public:
    static ProvinciasModel *InstanceModel();

    void AnadirProvincia(const Provincia *prov);

signals:

    void actualizado();

protected:
    ProvinciasModel();
    ProvinciasModel(const ProvinciasModel &);
    ProvinciasModel &operator =(const ProvinciasModel &);

private:
    static ProvinciasModel *pInstance;
    static void DestroyMe();

};

#endif // PROVINCIASMODEL_H
