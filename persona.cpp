#include "persona.h"

Persona::Persona()
{

}

void Persona::setNombre(QString n){
    if (n.isEmpty())
        nombre = n;
}

void Persona::setApellidos(QString a){
    if (a.isEmpty())
        apellidos = a;
}

void Persona::setBuscado(bool b){
    buscado = b;
}

void Persona::setWiki(bool w){
    wiki = w;
}

void Persona::setViaf(bool v){
    viaf = v;
}

void Persona::setWikilink(QString wl){
    wikilink = wl;
}

void Persona::setViaflink(QString vl){
    viaflink = vl;
}

void Persona::setNacimiento(QString nac){
    nacimiento = nac;
}

void Persona::setMuerte(QString m){
    muerte = m;
}

void Persona::setOtrosnombres(QString o){
    otrosnombres = o;
}

void Persona::setOtrosdatos(QString o){
    otrosdatos = o;
}

void Persona::setNotas(QString n){
    notas = n;
}
