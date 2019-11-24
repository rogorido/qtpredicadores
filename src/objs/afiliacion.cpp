#include "afiliacion.h"

Afiliacion::Afiliacion() {}

void Afiliacion::setPersona(const Persona p) { persona = p; }
void Afiliacion::setCasaOrigen(const Casa c) { casa_origen = c; }
void Afiliacion::setCasaDestino(const Casa c) { casa_destino = c; }
void Afiliacion::setProvinciaOrigen(const Provincia p) { provincia_origen = p; }
void Afiliacion::setProvinciaDestino(const Provincia p)
{
  provincia_destino = p;
}
void Afiliacion::setNotas(const Notas n) { nota = n; }
void Afiliacion::setExtras(const ExtraInfos e) { extras = e; }

QJsonObject Afiliacion::getAfiliacionJson()
{
  QJsonObject json;

  json.insert("afiliacion", "yes");

  if (persona.estaLleno()) json.insert("persona", QJsonValue(persona.getId()));

  if (casa_origen.estaLleno()) json.insert("casa_origen", casa_origen.getId());

  if (casa_destino.estaLleno())
    json.insert("casa_destino", casa_destino.getId());

  if (provincia_origen.estaLleno())
    json.insert("provincia_origen", provincia_origen.getId());

  if (provincia_destino.estaLleno())
    json.insert("provincia_destino", provincia_destino.getId());

  if (nota.estaLleno()) {
    json.insert("meta_info", nota.getNotasJson());
  }

  if (extras.size() > 0) {
    for (int i = 0; i < extras.size(); ++i) {
      QPair<QString, QString> valores;
      valores = extras.at(i);

      json.insert(valores.first, valores.second);
    }
  }

  return json;
}
