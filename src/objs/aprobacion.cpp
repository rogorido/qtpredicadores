#include "aprobacion.h"

Aprobacion::Aprobacion() {}

void Aprobacion::setTipoAprobacion(const Aprobacion::TipoAprobacion t)
{
  tipo_aprobacion = t;
}
void Aprobacion::setCargo(const QString c) { cargo = c; }
void Aprobacion::setTipoInstitucion(const QString t) { tipo_institucion = t; }
void Aprobacion::setPersona(const Persona p) { persona = p; }
void Aprobacion::setCasa(const Casa c) { casa = c; }
void Aprobacion::setProvincia(const Provincia p) { provincia = p; }
void Aprobacion::setExtraInfos(const ExtraInfos e) { extras = e; }
void Aprobacion::setNotas(const Notas n) { nota = n; }

QJsonObject Aprobacion::getAprobacionJson()
{
  QJsonObject json;

  json.insert("aprobación", "yes");

  if (tipo_aprobacion == Aprobacion::TipoAprobacion::PERSONA)
    json.insert("aprobación_tipo", "persona");
  else
    json.insert("aprobación_tipo", "casa");

  if (!cargo.isEmpty()) json.insert("aprobación_cargo", cargo);

  if (!tipo_institucion.isEmpty())
    json.insert("tipo_institucion", tipo_institucion);

  if (persona.estaLleno()) json.insert("persona", persona.getId());

  if (casa.estaLleno()) json.insert("casa", casa.getId());

  if (provincia.estaLleno()) json.insert("provincia", provincia.getId());

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

  return json;
}
