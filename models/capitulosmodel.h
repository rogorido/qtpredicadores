#ifndef CAPITULOSMODEL_H
#define CAPITULOSMODEL_H

#include <QSqlTableModel>

class Capitulo;

class CapitulosModel : public QSqlTableModel
{
    Q_OBJECT

public:
    static CapitulosModel *InstanceModel();

    bool AnadirCapitulo(const Capitulo *capitulo);

signals:

    void actualizado();

protected:
    CapitulosModel();
    CapitulosModel(const CapitulosModel &);
    CapitulosModel &operator =(const CapitulosModel &);

private:
    static CapitulosModel *pInstance;
    static void DestroyMe();

};

#endif // CAPITULOSMODEL_H
