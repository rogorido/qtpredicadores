#ifndef DECLARACION_H
#define DECLARACION_H

#include <QString>
#include <QJsonObject>

#include "objs/infraccion.h"
#include "objs/pena.h"
#include "objs/notas.h"
#include "objs/persona.h"

class Declaracion
{
public:
    Declaracion();

    void setTipo(QString t);
    void setInfraccion(Infraccion i);
    void setPena(Pena p);
    void setPersona(Persona p);
    void setNota(Notas n);
    void setExtraInfos(ExtraInfos e);
    void setExtraJson(QJsonObject e);

    // getters
    QString getTipo() const {return tipo;}
    Infraccion getInfraccion() const {return infraccion;}
    Pena getPena() const {return pena;}
    Persona getPersona() const {return persona;}
    Notas getNota() const {return nota;}
    ExtraInfos getExtras() const {return extras;}
    QJsonObject getExtrajson() const {return extrajson;}

    QJsonObject getDeclaracionJson();

private:
    QString tipo;
    Infraccion infraccion;
    Pena pena;
    Persona persona; // tvz tendría que ser Qlist... o QList<int>
    Notas nota;
    ExtraInfos extras;
    QJsonObject extrajson; // esto casi debería ser una QList<QJsonObject>...

};

#endif // DECLARACION_H
