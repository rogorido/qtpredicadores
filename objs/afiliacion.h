#ifndef AFILIACION_H
#define AFILIACION_H

#include <QJsonObject>

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
    void setCasaOrigen(Casa c);
    void setCasaDestino(Casa c);
    void setProvinciaOrigen(Provincia p);
    void setProvinciaDestino(Provincia p);
    void setExtras(ExtraInfos e);

    // getters
    Persona getPersona() const { return persona; }
    Casa getCasaOrigen() const { return casa_origen; }
    Casa getCasaDestino() const { return casa_destino; }
    Provincia getProvinciaOrigen() const { return provincia_origen; }
    Provincia getProvinciaDestino() const { return provincia_destino; }
    ExtraInfos getExtras() const { return extras; }

    QJsonObject getAfiliacionJson();

private:
    Persona persona;
    Casa casa_origen;
    Casa casa_destino;
    Provincia provincia_origen;
    Provincia provincia_destino;
    ExtraInfos extras;

};

#endif // AFILIACION_H
