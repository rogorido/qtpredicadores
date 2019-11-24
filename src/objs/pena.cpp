#include "pena.h"

Pena::Pena() { lleno = false; }

void Pena::setPenasTipos(const QStringList p)
{
  penas_tipos = p;
  lleno = true;
}

void Pena::setPenaTexto(const QString p) { pena_texto = p; }
void Pena::setDuracion(const QString d) { duracion = d; }
void Pena::setRestriccion(const QString r) { restriccion = r; }
void Pena::setAbsolucion(const QString a) { absolucion = a; }
void Pena::setPenados(const QStringList p)
{
  penados = p;
  lleno = true;
}
void Pena::setMotivo(const QString m) { motivo = m; }
void Pena::setExtraInfos(const ExtraInfos e) { extras = e; }
void Pena::setNotas(const Notas n) { nota = n; }

QJsonObject Pena::getPenaJson()
{
  QJsonObject json;

  json.insert("pena", "yes");

  if (!penas_tipos.isEmpty())
    json.insert("pena_tipos", QJsonArray::fromStringList(penas_tipos));

  if (!duracion.isEmpty()) json.insert("duración", duracion);

  if (!penados.isEmpty())
    json.insert("penados", QJsonArray::fromStringList(penados));

  if (!motivo.isEmpty()) json.insert("pena_motivo", motivo);

  if (!absolucion.isEmpty()) json.insert("pena_absolución", absolucion);

  if (!pena_texto.isEmpty()) json.insert("pena_texto", pena_texto);

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
