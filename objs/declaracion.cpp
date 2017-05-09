#include "declaracion.h"

Declaracion::Declaracion()
{

}

void Declaracion::setTipo(QString t) { tipo = t; }
void Declaracion::setInfraccion(Infraccion i) { infraccion = i; }
void Declaracion::setPena(Pena p) { pena = p; }
void Declaracion::setPersona(Persona p) { persona = p; }
void Declaracion::setNota(Notas n) { nota = n; }
void Declaracion::setExtraInfos(ExtraInfos e) { extras = e; }
void Declaracion::setExtraJson(QJsonObject e) { extrajson = e; }

QJsonObject Declaracion::getDeclaracionJson(){

}

