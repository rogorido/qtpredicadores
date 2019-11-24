#include "retroreferencia.h"

RetroReferencia::RetroReferencia() { lleno = false; }

void RetroReferencia::setTipo(const QString t)
{
  tipo = t;
  lleno = true;
}

void RetroReferencia::setReferencia(const QString r) { referencia = r; }
void RetroReferencia::setTextoReal(const QString t) { texto_real = t; }

QJsonObject RetroReferencia::getRetroJson()
{
  QJsonObject json;

  if (lleno) json.insert("retro", "yes");

  if (!tipo.isEmpty()) json.insert("tipo_retro", tipo);

  if (!referencia.isEmpty()) json.insert("referencia", referencia);

  if (!texto_real.isEmpty()) json.insert("textoreal_retro", texto_real);

  return json;
}
