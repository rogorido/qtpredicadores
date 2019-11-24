#include "viaje.h"

#include <QJsonArray>
#include <QJsonObject>

Viaje::Viaje() {}

void Viaje::setOriginal(const bool o) { original = o; }
void Viaje::setOrigen(const int o) { origen = o; }
void Viaje::setDestino(const int d) { destino = d; }
void Viaje::setMotivos(const QStringList m) { motivos = m; }
void Viaje::setDuracion(const int d) { duracion = d; }
void Viaje::setVuelta(const bool v) { vuelta = v; }
void Viaje::setMuerto(const bool m) { muerto = m; }
void Viaje::setMotivoMuerte(const QString m) { motivo_muerte = m; }
void Viaje::setLugarMuerte(const QString l) { lugar_muerte = l; }
void Viaje::setFechaInicio(const QDate f) { fecha_inicio = f; }
void Viaje::setFechaFin(const QDate f) { fecha_fin = f; }
void Viaje::setNotas(const Notas n) { nota = n; }

QJsonObject Viaje::getViajeJson()
{
  QJsonObject viaje_final;
  QJsonObject viaje;

  viaje.insert("original", QJsonValue(original));

  if (origen != 0) viaje.insert("viaje_origen", origen);

  if (destino != 0) viaje.insert("viaje_destino", destino);

  if (duracion != 0) viaje.insert("duración", duracion);

  if (!motivos.isEmpty())
    viaje.insert("motivos", QJsonArray::fromStringList(motivos));

  viaje.insert("muerto", QJsonValue(muerto));

  if (!motivo_muerte.isEmpty())
    viaje.insert("motivo_muerte", QJsonValue(motivo_muerte));

  if (!lugar_muerte.isEmpty())
    viaje.insert("lugar_muerte", QJsonValue(lugar_muerte));

  if (fecha_inicio != QDate(1500, 1, 1))
    viaje.insert("fecha_inicio", fecha_inicio.toString("dd-MM-yyyy"));

  if (fecha_fin != QDate(1500, 1, 1))
    viaje.insert("fecha_fin", fecha_fin.toString("dd-MM-yyyy"));

  viaje.insert("vuelta", QJsonValue(vuelta));

  if (nota.estaLleno()) viaje.insert("meta_info", nota.getNotasJson());

  viaje_final.insert("viaje", viaje);

  return viaje_final;
}
