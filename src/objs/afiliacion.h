#ifndef AFILIACION_H
#define AFILIACION_H

#include <QJsonObject>

#include "variados.h"
#include "persona.h"
#include "casa.h"
#include "provincia.h"
#include "notas.h"

class Afiliacion
{
public:
    Afiliacion();

    // setters
    void setPersona(const Persona p);
    void setCasaOrigen(const Casa c);
    void setCasaDestino(const Casa c);
    void setProvinciaOrigen(const Provincia p);
    void setProvinciaDestino(const Provincia p);
    void setNotas(const Notas n);
    void setExtras(const ExtraInfos e);

    // getters
    Persona getPersona() const { return persona; }
    Casa getCasaOrigen() const { return casa_origen; }
    Casa getCasaDestino() const { return casa_destino; }
    Provincia getProvinciaOrigen() const { return provincia_origen; }
    Provincia getProvinciaDestino() const { return provincia_destino; }
    Notas getNota() const { return nota; }
    ExtraInfos getExtras() const { return extras; }

    QJsonObject getAfiliacionJson();

private:
    Persona persona;
    Casa casa_origen;
    Casa casa_destino;
    Provincia provincia_origen;
    Provincia provincia_destino;
    Notas nota;
    ExtraInfos extras;

};

#endif // AFILIACION_H
