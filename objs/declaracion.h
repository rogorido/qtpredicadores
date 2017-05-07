#ifndef DECLARACION_H
#define DECLARACION_H

#include <QString>
#include <QJsonObject>

#include "objs/infraccion.h"
#include "objs/pena.h"
#include "objs/notas.h"

class Declaracion
{
public:
    Declaracion();

    void setTipo(QString t);
    void setInfraccion(Infraccion i);
    void setPena(Pena p);
    void setNota(Nota n);
    void setExtraInfos(ExtraInfos e);
    void setExtraJson(QJsonObject e);

    // getters
    QString getTipo() const {return tipo;}
    Infraccion getInfraccion() const {return infraccion;}
    Pena getPena() const {return pena;}
    Notas getNota() const {return nota;}
    ExtraInfos getExtras() const {return extras;}
    QJsonObject getExtrajson() const {return extrajson;}

    QJsonObject getDeclaracionJson();

private:
    QString tipo;
    Infraccion infraccion;
    Pena pena;
    Notas nota;
    ExtraInfos extras;
    QJsonObject extrajson; // esto casi debería ser una QList<QJsonObject>...

};

#endif // DECLARACION_H
