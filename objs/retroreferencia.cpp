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

QJsonObject RetroReferencia::getRetroJson()
{
    QJsonObject json;

    json.insert("tipo_retro", tipo);
    json.insert("referencia", referencia);
    json.insert("textoreal_retro", texto_real);

    return json;
}

