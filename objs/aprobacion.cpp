#include "aprobacion.h"

Aprobacion::Aprobacion() { }

void Aprobacion::setTipo(QString t) { tipo = t; }
void Aprobacion::setPersona(Persona p) { persona = p; }
void Aprobacion::setProvincia(Provincia p) { provincia = p; }
void Aprobacion::setExtraInfos(ExtraInfos e) { extras = e; }

QJsonObject Aprobacion::getAprobacionJson()
{
    QJsonObject json;

    json.insert("aprobación", "yes");

    if (!tipo.isEmpty())
        json.insert("aprobación_tipo", tipo);

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
