#ifndef RESOLUCIONESMODEL_H
#define RESOLUCIONESMODEL_H

#include <QSqlTableModel>

class Resolucion;

class ResolucionesModel : public QSqlTableModel
{
    Q_OBJECT

public:
    static ResolucionesModel *InstanceModel();

    bool anadirResolucion(const Resolucion *resolucion);

signals:

    void actualizado();

protected:
    ResolucionesModel();
    ResolucionesModel(const ResolucionesModel &);
    ResolucionesModel &operator =(const ResolucionesModel &);

private:
    static ResolucionesModel *pInstance;
    static void DestroyMe();

};

#endif // RESOLUCIONESMODEL_H
