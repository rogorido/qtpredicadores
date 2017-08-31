#ifndef INFRACCION_H
#define INFRACCION_H

#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>

#include "objs/variados.h"
#include "objs/notas.h"

class Infraccion
{
public:
    Infraccion();

    // setters
    void setTipo(QString t);
    void setInfraccion(QString i);
    void setInfractores(QStringList i);
    void setNota(Notas n);
    void setExtras(ExtraInfos e);

    // getters

    QString getTipo() const {return tipo;}
    QString getInfraccion() const {return infraccion;}
    QStringList getInfractores() const {return infractores;}
    Notas getNota() const {return nota;}
    ExtraInfos getExtras() const {return extras;}
    bool estaLleno() const {return lleno;}

    QJsonObject getInfraccionJson();

private:

    QString tipo;
    QString infraccion;
    QStringList infractores;
    Notas nota;
    ExtraInfos extras;
    bool lleno = false;

    /*
     * meter o no meter temas? Teniendo en cuenta que esto
     * debería ir más bien dentro de otra cosa, no sé...
     */

};

#endif // INFRACCION_H
