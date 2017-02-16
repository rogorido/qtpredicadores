#ifndef CASASMODEL_H
#define CASASMODEL_H

#include <QSqlTableModel>

class Casa;

class CasasModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit CasasModel(QObject *parent = 0);

    void AnadirCasa(const Casa *casa);

signals:

public slots:
};

#endif // CASASMODEL_H
