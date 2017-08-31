#include "declaracion.h"

Declaracion::Declaracion() { }

void Declaracion::setTipo(QString t) { tipo = t; }
void Declaracion::setInfraccion(Infraccion i) { infraccion = i; }
void Declaracion::setPena(Pena p) { pena = p; }
void Declaracion::setPersona(Persona p) { persona = p; }
void Declaracion::setNota(Notas n) { nota = n; }
void Declaracion::setExtraInfos(ExtraInfos e) { extras = e; }
void Declaracion::setExtraJson(QJsonObject e) { extrajson = e; }

QJsonObject Declaracion::getDeclaracionJson(){

    QJsonObject json;

    json.insert("declaracion", "yes");

    if (!tipo.isEmpty())
        json.insert("declaracion_tipo", tipo);

    if (pena.estaLleno())
        json.insert("declaracion_pena", pena.getPenaJson());

    if (infraccion.estaLleno())
        json.insert("declaracion_infraccion", infraccion.getInfraccionJson());

    if (persona.estaLleno()){
        json.insert("declaracion_persona", persona.getId());
    }

    if (extras.size() > 0 ) {
        for (int i = 0; i < extras.size(); ++i) {
            QPair<QString, QString> valores;
            valores = extras.at(i);

            json.insert(valores.first, valores.second);
        }
    }

    if (nota.estaLleno()){
        json.insert("declaracion_nota", nota.getNotasJson());
    }

    // y aqí rtt qué coño va...
    //json.insert("declaracion_otros", extrajson);

    return json;

}

