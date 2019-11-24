#include "notas.h"

Notas::Notas() {}

void Notas::setVolverMirar(const bool v)
{
  volveramirar = v;
  lleno = true;
}

void Notas::setInteresante(const bool i)
{
  interesante = i;
  lleno = true;
}

void Notas::setNota(const QString n)
{
  nota = n;
  lleno = true;
}

void Notas::setSeguridad(const int s)
{
  seguridad = s;
  lleno = true;
}

QJsonObject Notas::getNotasJson()
{
  QJsonObject json;

  json.insert("volver_a_mirar", QJsonValue(volveramirar));
  json.insert("interesante", QJsonValue(interesante));
  json.insert("seguridad", QJsonValue(seguridad));
  json.insert("nota", nota);

  return json;
}
