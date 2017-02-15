#ifndef CASAS_H
#define CASAS_H

#include <QSqlTableModel>

class Casas : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit Casas(QObject *parent = 0);

    void AnadirCasa(const QString casa);

signals:

public slots:
};

#endif // CASAS_H
