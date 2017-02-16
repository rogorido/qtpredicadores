#ifndef PERSONAS_H
#define PERSONAS_H

#include <QSqlTableModel>

class Persona;

class Personas : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit Personas(QObject *parent = 0);

    void AnadirPersona(const Persona *persona);

signals:

public slots:
};

#endif // PERSONAS_H
