#ifndef AFILIACION_H
#define AFILIACION_H

#include "objs/variados.h"
#include "objs/persona.h"
#include "objs/casa.h"
#include "objs/provincia.h"

class Afiliacion
{
public:
    Afiliacion();

    // setters
    void setPersona(Persona p);
    void setCasa(Casa c);
    void setProvincia(Provincia p);
    void setExtras(ExtraInfos e);

    // getters
    Persona getPersona() const { return persona; }
    Casa getCasa() const { return casa; }
    Provincia getProvincia() const { return provincia; }
    ExtraInfos getExtras() const { return extras; }


private:
    Persona persona;
    Casa casa;
    Provincia provincia;
    ExtraInfos extras;

};

#endif // AFILIACION_H
