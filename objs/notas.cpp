#include "notas.h"

Notas::Notas() { }

void Notas::setVolverMirar(bool v) {
    volveramirar = v;
    lleno = true;
}
void Notas::setNota(QString n) {
    nota = n;
    lleno = true;
}

QJsonObject Notas::getNotasJson()
{
    QJsonObject json;

    json.insert("volver_a_mirar", QJsonValue(volveramirar));
    json.insert("nota", nota);

    return json;
}


