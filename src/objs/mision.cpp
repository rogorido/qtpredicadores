#include "mision.h"

#include <QJsonDocument>

Mision::Mision() { }

void Mision::setId(const int i) { id = i; }
void Mision::setNumeroMision(const int n) { numero_mision = n; }
void Mision::setLugarSalida(const int l) { lugar_salida = l; }
void Mision::setFechaSalida(const QDate f){ fecha_salida = f; }
void Mision::setFechaLlegada(const QDate f) { fecha_llegada = f; }
void Mision::setEtapas(const QString e) { etapas = e; }
void Mision::setNota(const Notas n) { nota = n; }
