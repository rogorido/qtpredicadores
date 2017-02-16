#ifndef TEMASMODEL_H
#define TEMASMODEL_H

#include <QSqlTableModel>

class TemasModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit TemasModel(QObject *parent = 0);

    void AnadirTema(const QString tema);

signals:

public slots:

};

#endif // TEMASMODEL_H
