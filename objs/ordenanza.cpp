#include "ordenanza.h"

Ordenanza::Ordenanza() { }

void Ordenanza::setTipo(TipoOrdenanza t) { tipo_ordenanza = t; }
void Ordenanza::setReceptores(QStringList r) { receptores = r; }
void Ordenanza::setObjetos(QStringList o) { objetos = o; }
void Ordenanza::setPena(Pena p) { pena = p; }
void Ordenanza::setRestriccion(QString r) { restriccion = r; }
void Ordenanza::setFinalidades(QStringList f) { finalidades = f; }
void Ordenanza::setSeguridad(int s) { seguridad = s; }
void Ordenanza::setRetroReferencia(RetroReferencia r) { retro = r; }
void Ordenanza::setTemas(QList<int> t) { temas = t; }
void Ordenanza::setExtraInfos(ExtraInfos e) { extras = e; }
void Ordenanza::setNota(Notas n) { nota = n; }

QJsonObject Ordenanza::getOrdenanzaJson()
{
    QJsonObject json;

    if (tipo_ordenanza == TipoOrdenanza::PROHIBICION)
        json.insert("prohibición", "yes");
    else
        json.insert("mandato", "yes");

    if (!objetos.isEmpty())
        json.insert("objetos", QJsonArray::fromStringList(objetos));

    if (!receptores.isEmpty())
        json.insert("destinatarios", QJsonArray::fromStringList(receptores));

    if (!restriccion.isEmpty())
        json.insert("restricción", restriccion);

    json.insert("seguridad", QJsonValue(seguridad));

    if (pena.estaLleno()){
        json.insert("pena", pena.getPenaJson());
    }

    if (retro.estaLleno())
        json.insert("retro", retro.getRetroJson());

    if (!temas.isEmpty()){
        QJsonArray array_temas;
        for (int i = 0; i < temas.size(); ++i) {
            array_temas.append(QJsonValue(temas.at(i)));
        }

        json.insert("temas", array_temas);
    }

    if (extras.size() > 0 ) {
        for (int i = 0; i < extras.size(); ++i) {
            QPair<QString, QString> valores;
            valores = extras.at(i);

            json.insert(valores.first, valores.second);
        }
    }

    return json;

}
