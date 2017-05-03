#include "retroreferencia.h"

RetroReferencia::RetroReferencia()
{ lleno = false; }

void RetroReferencia::setTipo(QString t)
{
    tipo = t;
    lleno = true;
}

void RetroReferencia::setReferencia(QString r) { referencia = r; }
void RetroReferencia::setTextoReal(QString t) { texto_real = t; }

