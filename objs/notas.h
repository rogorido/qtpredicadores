#ifndef NOTAS_H
#define NOTAS_H

#include <QString>
#include <QJsonObject>

class Notas
{
public:
    Notas();

    // setters
    void setVolverMirar(bool v);
    void setNota(QString n);

    // getters
    bool getVolverMirar() const {return volveramirar;}
    QString getNota() const {return nota;}

    QJsonObject getNotas();

private:
    bool volveramirar = false;
    QString nota;

};

#endif // NOTAS_H
