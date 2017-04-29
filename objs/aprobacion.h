#ifndef APROBACION_H
#define APROBACION_H

#include <QString>
#include "objs/variados.h"
#include "objs/persona.h"
#include "objs/provincia.h"

class Aprobacion
{
public:
    Aprobacion();

    //setters
    void setTipo(QString t);
    void setPersona(Persona p);
    void setProvincia(Provincia p);

    //getters
    QString getTipo() const {return tipo;}
    Persona getPersona() const {return persona;}
    Provincia getProvincia() const {return provincia;}

private:
    QString tipo;
    Persona persona;
    Provincia provincia;

};

#endif // APROBACION_H
