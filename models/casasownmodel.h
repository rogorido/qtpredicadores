#ifndef CASASOWNMODEL_H
#define CASASOWNMODEL_H

#include <QSqlQueryModel>
#include <QIcon>

class CasasOwnModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit CasasOwnModel(QObject *parent = 0);

    QVariant data(const QModelIndex &item, int role) const override;

private:

    QIcon icono_masculino;
    QIcon icono_femenino;

};

#endif // CASASOWNMODEL_H
