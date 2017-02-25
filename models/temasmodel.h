#ifndef TEMASMODEL_H
#define TEMASMODEL_H

#include <QSqlTableModel>

class TemasModel : public QSqlTableModel
{
    Q_OBJECT

public:
    static TemasModel *InstanceModel();

    void AnadirTema(const QString &tema);

protected:
    TemasModel();
    TemasModel(const TemasModel &);
    TemasModel &operator =(const TemasModel &);

private:
    static TemasModel *pInstance;
    static void DestroyMe();
};

#endif // TEMASMODEL_H
