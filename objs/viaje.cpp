#include "viaje.h"

#include <QJsonObject>
#include <QJsonArray>

Viaje::Viaje() { }

void Viaje::setOriginal(bool o) { original = o; }
void Viaje::setOrigen(int o) { origen = o; }
void Viaje::setDestino(int d) { destino = d; }
void Viaje::setMotivos(QStringList m) { motivos = m; }
void Viaje::setDuracion(int d) { duracion = d; }
void Viaje::setMuerto(bool m) { muerto = m; }
void Viaje::setMotivoMuerte(QString m) { motivo_muerte = m; }
void Viaje::setLugarMuerte(QString l) { lugar_muerte = l; }
void Viaje::setFechaInicio(QDate f) { fecha_inicio = f; }
void Viaje::setFechaFin(QDate f) { fecha_fin = f; }
void Viaje::setNotas(Notas n) { nota = n; }

QJsonObject Viaje::getViajeJson()
{
    QJsonObject viaje_final;
    QJsonObject viaje;

    viaje.insert("original", QJsonValue(original));

    if (origen != 0)
        viaje.insert("viaje_origen", origen);

    if (destino != 0)
        viaje.insert("viaje_destino", destino);

    if (duracion != 0)
        viaje.insert("duración", duracion);

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

    if (nota.estaLleno())
        viaje.insert("meta_info", nota.getNotasJson());

    viaje_final.insert("viaje", viaje);

    return viaje_final;

}
