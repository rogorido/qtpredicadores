#include "notas.h"

Notas::Notas() { }

void Notas::setVolverMirar(bool v) { volveramirar = v; }
void Notas::setNota(QString n) { nota = n; }

QJsonObject Notas::getNotas()
{
    QJsonObject json;

    json.insert("volver_a_mirar", QJsonValue(volveramirar));
    json.insert("nota", nota);

    return json;
}


