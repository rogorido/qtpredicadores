#include "afiliacion.h"

Afiliacion::Afiliacion() { }

void Afiliacion::setPersona(Persona p) { persona = p; }
void Afiliacion::setCasaOrigen(Casa c) { casa_origen = c; }
void Afiliacion::setCasaDestino(Casa c) { casa_destino = c; }
void Afiliacion::setProvinciaOrigen(Provincia p) { provincia_origen = p; }
void Afiliacion::setProvinciaDestino(Provincia p) { provincia_destino = p; }
void Afiliacion::setExtras(ExtraInfos e) { extras = e; }
