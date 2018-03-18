#ifndef RETROREFERENCIA_H
#define RETROREFERENCIA_H

#include <QJsonObject>

#include "objs/variados.h"

class RetroReferencia
{
public:
    RetroReferencia();

    // setters

    void setTipo(const QString t);
    void setReferencia(const QString r);
    void setTextoReal(const QString t);

    // getters
    QString getTipo() const {return tipo;}
    QString getReferencia() const {return referencia;} // es un valor/resumen que pongo yo
    QString getTextoTeal() const {return texto_real;}
    bool estaLleno() const {return lleno;}

    // devolver un QJsonObject
    QJsonObject getRetroJson();

private:

    QString tipo;
    QString referencia; // es un valor/resumen que pongo yo
    QString texto_real;
    bool lleno = false;


};

#endif // RETROREFERENCIA_H
