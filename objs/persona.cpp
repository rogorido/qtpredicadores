#include "persona.h"

Persona::Persona() { lleno = false; }

void Persona::setId(int i){ id = i; }
void Persona::setNombre(QString n)
{
    nombre = n;
    lleno = true;
}
void Persona::setApellidos(QString a){ apellidos = a; }
void Persona::setOrigen(QString o){ origen = o; }
void Persona::setBuscado(bool b){ buscado = b; }
void Persona::setWiki(bool w){ wiki = w; }
void Persona::setViaf(bool v){ viaf = v; }
void Persona::setWikilink(QString wl){ wikilink = wl; }
void Persona::setViaflink(QString vl){ viaflink = vl; }
void Persona::setWikidata(QString w) { wikidata = w; }
void Persona::setNacimiento(QString nac){ nacimiento = nac; }
void Persona::setMuerte(QString m){ muerte = m; }
void Persona::setDiocesis(QString d) { diocesis = d; }
void Persona::setOtrosnombres(QString o){ otrosnombres = o; }
void Persona::setOtrosdatos(QString o){ otrosdatos = o; }
void Persona::setVolverMirar(bool v) { volveramirar = v; }
void Persona::setCantidadInfo(int c) { cantidadinfo = c; }
void Persona::setNotas(QString n){ notas = n; }
