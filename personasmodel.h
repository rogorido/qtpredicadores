#ifndef PERSONASMODEL_H
#define PERSONASMODEL_H

#include <QSqlTableModel>

class Persona;

class PersonasModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit PersonasModel(QObject *parent = 0);

    void AnadirPersona(const Persona *persona);

signals:

public slots:
};

#endif // PERSONASMODEL_H
