#ifndef LUGARESMODEL_H
#define LUGARESMODEL_H

#include <QSqlTableModel>

class LugaresModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit LugaresModel(QObject *parent = 0);

    void AnadirLugar(const QString lugar);

signals:

public slots:
};

#endif // LUGARESMODEL_H
