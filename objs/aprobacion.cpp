#include "aprobacion.h"

Aprobacion::Aprobacion() { }

void Aprobacion::setTipo(QString t) { tipo = t; }
void Aprobacion::setPersona(Persona p) { persona = p; }
void Aprobacion::setProvincia(Provincia p) { provincia = p; }
void Aprobacion::setExtraInfos(ExtraInfos e) { extras = e; }
