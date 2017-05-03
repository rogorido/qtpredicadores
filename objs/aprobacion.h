#ifndef APROBACION_H
#define APROBACION_H

#include <QString>
#include <QJsonObject>

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
    void setExtraInfos(ExtraInfos e);

    //getters
    QString getTipo() const {return tipo;}
    Persona getPersona() const {return persona;}
    Provincia getProvincia() const {return provincia;}
    ExtraInfos getExtraInfos() const { return extras; }

    QJsonObject getAprobacionJson();

private:
    QString tipo;
    Persona persona;
    Provincia provincia;
    ExtraInfos extras;

};

#endif // APROBACION_H
