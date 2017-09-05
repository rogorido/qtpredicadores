#include "aprobacion.h"

Aprobacion::Aprobacion() { }

void Aprobacion::setTipoAprobacion(Aprobacion::TipoAprobacion t) { tipo_aprobacion = t; }
void Aprobacion::setCargo(QString c) { cargo = c; }
void Aprobacion::setPersona(Persona p) { persona = p; }
void Aprobacion::setProvincia(Provincia p) { provincia = p; }
void Aprobacion::setExtraInfos(ExtraInfos e) { extras = e; }

QJsonObject Aprobacion::getAprobacionJson()
{
    QJsonObject json;

    json.insert("aprobación", "yes");

    if (tipo_aprobacion == Aprobacion::TipoAprobacion::PERSONA)
        json.insert("aprobación_tipo", "persona");
    else
        json.insert("aprobación_tipo", "casa");

    /*
     * esto es el tipo de cargo, etc.
     */
    if (!cargo.isEmpty())
        json.insert("aprobación_cargo", cargo);

    if (persona.estaLleno())
        json.insert("persona", persona.getId());

    if (provincia.estaLleno())
        json.insert("provincia", provincia.getId());

    if (extras.size() > 0 ) {
        for (int i = 0; i < extras.size(); ++i) {
            QPair<QString, QString> valores;
            valores = extras.at(i);

            json.insert(valores.first, valores.second);
        }
    }

    return json;
}
