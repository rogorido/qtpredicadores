#include "ordenanza.h"

Ordenanza::Ordenanza() { }

void Ordenanza::setTipo(TipoOrdenanza t) { tipo_ordenanza = t; }
void Ordenanza::setReceptores(QStringList r) { receptores = r; }
void Ordenanza::setObjetos(QStringList o) { objetos = o; }
void Ordenanza::setPena(Pena p) { pena = p; }
void Ordenanza::setRestriccion(QString r) { restriccion = r; }
void Ordenanza::setFinalidades(QStringList f) { finalidades = f; }
void Ordenanza::setSeguridad(int s) { seguridad = s; }
void Ordenanza::setRetroReferencia(RetroReferencia r) { retro = r; }
void Ordenanza::setExtraInfos(ExtraInfos e) { extras = e; }
