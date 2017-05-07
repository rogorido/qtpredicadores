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
    bool estaLleno() const {return lleno;}

    QJsonObject getNotasJson();

private:
    bool volveramirar = false;
    QString nota;
    bool lleno = false;

};

#endif // NOTAS_H
