#include "lugar.h"

Lugar::Lugar() { }

void Lugar::setId(const int i) { id = i; }
void Lugar::setLugar(const QString l) { lugar = l; }
void Lugar::setLugarLatin(const QString l) { lugar_latin = l; }
void Lugar::setPais(const QString p) { pais = p; }
void Lugar::setOtrosNombres(const QString o) { otros_nombres = o; }
void Lugar::setWikidata(const QString w) { wikidata = w; }
void Lugar::setTipoLugar(const QString t) { tipo_lugar = t; }

