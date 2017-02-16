#ifndef LUGARES_H
#define LUGARES_H

#include <QSqlTableModel>

class Lugares : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit Lugares(QObject *parent = 0);

    void AnadirLugar(const QString lugar);

signals:

public slots:
};

#endif // LUGARES_H
