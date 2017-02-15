#ifndef TEMAS_H
#define TEMAS_H

#include <QSqlTableModel>

class Temas : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit Temas(QObject *parent = 0);

    void AnadirTema(const QString tema);

signals:

public slots:

};

#endif // TEMAS_H
