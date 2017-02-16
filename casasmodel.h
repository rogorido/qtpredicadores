#ifndef CASASMODEL_H
#define CASASMODEL_H

#include <QSqlTableModel>

class CasasModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit CasasModel(QObject *parent = 0);

    void AnadirCasa(const QString casa);

signals:

public slots:
};

#endif // CASASMODEL_H
