#ifndef APROBACION_H
#define APROBACION_H

#include <QString>
#include "objs/variados.h"

class Aprobacion
{
public:
    Aprobacion();

    //setters
    void setTipo(QString t);
    void setPersona(elementopareado p);
    void setProvincia(elementopareado p);

    //getters
    QString getTipo() const {return tipo;}
    elementopareado getPersona() const {return persona;}
    elementopareado getProvincia() const {return provincia;}

private:
    QString tipo;
    elementopareado persona;
    elementopareado provincia;

};

#endif // APROBACION_H
