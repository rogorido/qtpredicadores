#ifndef TEMASMODEL_H
#define TEMASMODEL_H

#include <QSqlTableModel>

#include <src/objs/tema.h>

class TemasModel : public QSqlTableModel
{
    Q_OBJECT

public:
    static TemasModel *InstanceModel();

    bool AnadirTema(const Tema *tema);

signals:

    void actualizado();

protected:
    TemasModel();
    TemasModel(const TemasModel &);
    TemasModel &operator =(const TemasModel &);

private:
    static TemasModel *pInstance;
    static void DestroyMe();
};

#endif // TEMASMODEL_H
