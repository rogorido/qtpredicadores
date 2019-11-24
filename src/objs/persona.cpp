#include "persona.h"

Persona::Persona() { lleno = false; }

void Persona::setId(const int i) { id = i; }
void Persona::setNombre(const QString n)
{
  nombre = n;
  lleno = true;
}
void Persona::setApellidos(const QString a) { apellidos = a; }
void Persona::setOrigen(const QString o) { origen = o; }
void Persona::setMasculino(const bool m) { masculino = m; }
void Persona::setBuscado(const bool b) { buscado = b; }
void Persona::setWiki(const bool w) { wiki = w; }
void Persona::setViaf(const bool v) { viaf = v; }
void Persona::setTipoPersona(const QString t) { tipo_persona = t; }
void Persona::setWikilink(const QString wl) { wikilink = wl; }
void Persona::setViaflink(const QString vl) { viaflink = vl; }
void Persona::setWikidata(const QString w) { wikidata = w; }
void Persona::setNacimiento(const QString nac) { nacimiento = nac; }
void Persona::setMuerte(const QString m) { muerte = m; }
void Persona::setDiocesis(const QString d) { diocesis = d; }
void Persona::setOtrosnombres(const QString o) { otrosnombres = o; }
void Persona::setOtrosdatos(const QString o) { otrosdatos = o; }
void Persona::setVolverMirar(const bool v) { volveramirar = v; }
void Persona::setCantidadInfo(const int c) { cantidadinfo = c; }
void Persona::setNotas(const QString n) { notas = n; }
void Persona::setFuente(const fuente f) { fuente_origen = f; }

QString Persona::getNombreCompleto() const
{
  QString nombre_completo =
      nombre + QString(' ') + apellidos + QString(' ') + origen;

  return nombre_completo;
}
