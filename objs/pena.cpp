#include "pena.h"

Pena::Pena() { lleno = false; }

void Pena::setPenasTipos(QStringList p)
{
    penas_tipos = p;
    lleno = true;
}

void Pena::setPenaTexto(QString p) { pena_texto = p; }
void Pena::setDuracion(QString d) { duracion = d; }
void Pena::setRestriccion(QString r) { restriccion = r; }
void Pena::setAbsolucion(QString a) { absolucion = a; }
void Pena::setPenados(QStringList p)
{
    penados = p;
    lleno = true;
}
void Pena::setMotivo(QString m) { motivo = m; }
void Pena::setExtraInfos(ExtraInfos e) { extras = e; }
void Pena::setNotas(Notas n) { nota = n; }

QJsonObject Pena::getPenaJson()
{
    QJsonObject json;

    json.insert("pena", "yes");

    if (!penas_tipos.isEmpty())
        json.insert("pena_tipos", QJsonArray::fromStringList(penas_tipos));

    if (!duracion.isEmpty())
        json.insert("duración", duracion);

    if (!penados.isEmpty())
        json.insert("penados", QJsonArray::fromStringList(penados));

    if (!motivo.isEmpty())
        json.insert("pena_motivo", motivo);

    if (!absolucion.isEmpty())
        json.insert("pena_absolución", absolucion);

    if (!pena_texto.isEmpty())
        json.insert("pena_texto", pena_texto);

    if (extras.size() > 0 ) {
        for (int i = 0; i < extras.size(); ++i) {
            QPair<QString, QString> valores;
            valores = extras.at(i);

            json.insert(valores.first, valores.second);
        }
    }

    if (nota.estaLleno()){
        json.insert("meta_info", nota.getNotasJson());
    }

    return json;

}
