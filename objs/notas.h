#ifndef NOTAS_H
#define NOTAS_H

#include <QString>
#include <QJsonObject>

class Notas
{
public:
    Notas();

    // setters
    void setVolverMirar(const bool v);
    void setInteresante(const bool i);
    void setSeguridad(const int s);
    void setNota(const QString n);

    // getters
    bool getVolverMirar() const {return volveramirar;}
    bool getInteresante() const {return interesante;}
    int getSeguridad() const {return seguridad;}
    QString getNota() const {return nota;}
    bool estaLleno() const {return lleno;}

    QJsonObject getNotasJson();

private:
    bool volveramirar = false;
    bool interesante = false;
    int seguridad;
    QString nota;
    bool lleno = false;

};

#endif // NOTAS_H
