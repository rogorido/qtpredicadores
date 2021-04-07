#include "declaracion.h"

#include <QJsonArray>

Declaracion::Declaracion() {}

void Declaracion::setTipo(const QString t) { tipo = t; }
void Declaracion::setInfraccion(const Infraccion i) { infraccion = i; }
void Declaracion::setPena(const Pena p) { pena = p; }
void Declaracion::setPersona(const Persona p) { persona = p; }
void Declaracion::setCargos(const QStringList c) { cargos = c; }
void Declaracion::setInstituciones(const QStringList i) { instituciones = i; }
void Declaracion::setProvincias(const QList<int> p) { provincias = p; }
void Declaracion::setRetroReferencia(const RetroReferencia r) { retro = r; }
void Declaracion::setNota(const Notas n) { nota = n; }
void Declaracion::setExtraInfos(const ExtraInfos e) { extras = e; }
void Declaracion::setExtraJson(const QJsonObject e) { extrajson = e; }

QJsonObject Declaracion::getDeclaracionJson()
{
  QJsonObject json;

  json.insert("declaracion", "yes");

  if (!tipo.isEmpty()) json.insert("declaracion_tipo", tipo);

  if (pena.estaLleno()) json.insert("declaracion_pena", pena.getPenaJson());

  if (infraccion.estaLleno())
    json.insert("declaracion_infraccion", infraccion.getInfraccionJson());

  if (persona.estaLleno()) {
    json.insert("declaracion_persona", persona.getId());
  }

  if (!cargos.isEmpty())
    json.insert("cargos", QJsonArray::fromStringList(cargos));

  if (!instituciones.isEmpty())
    json.insert("instituciones", QJsonArray::fromStringList(instituciones));

  if (!provincias.isEmpty()) {
    QJsonArray array_provincias;
    for (int i = 0; i < provincias.size(); ++i) {
      array_provincias.append(QJsonValue(provincias.at(i)));
    }

    json.insert("provincias", array_provincias);
  }

  if (retro.estaLleno()) json.insert("retro_info", retro.getRetroJson());

  if (extras.size() > 0) {
    for (int i = 0; i < extras.size(); ++i) {
      QPair<QString, QString> valores;
      valores = extras.at(i);

      json.insert(valores.first, valores.second);
    }
  }

  if (nota.estaLleno()) {
    json.insert("meta_info", nota.getNotasJson());
  }

  // y aqí rtt qué coño va...
  // json.insert("declaracion_otros", extrajson);

  return json;
}
