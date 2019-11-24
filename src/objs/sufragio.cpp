#include "sufragio.h"

Sufragio::Sufragio() {}

void Sufragio::setTipo(const QString t) { tipo = t; }
void Sufragio::setMisas(const int m) { misas = m; }
void Sufragio::setMotivo(const QString m) { motivo = m; }
void Sufragio::setDestinatarios(const QStringList d) { destinatarios = d; }
void Sufragio::setExtraInfos(const ExtraInfos e) { extras = e; }
void Sufragio::setNota(const Notas n) { nota = n; }

QJsonObject Sufragio::getSufragioJson()
{
  QJsonObject json;

  json.insert("sufragio", "yes");

  if (!motivo.isEmpty()) json.insert("motivo", motivo);

  if (misas != 0) json.insert("misas", QJsonValue(misas));

  if (!destinatarios.isEmpty())
    json.insert("destinatarios", QJsonArray::fromStringList(destinatarios));

  if (extras.size() > 0) {
    for (int i = 0; i < extras.size(); ++i) {
      QPair<QString, QString> valores;
      valores = extras.at(i);

      json.insert(valores.first, valores.second);
    }
  }

  if (nota.estaLleno()) json.insert("meta_info", nota.getNotasJson());

  return json;
}
