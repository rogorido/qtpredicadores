#include "mision.h"

Mision::Mision()
{ }

void Mision::setId(int i) { id = i; }
void Mision::setLugarSalida(int l) { lugar_salida = l; }
void Mision::setFechaSalida(QDate f){ fecha_salida = f; }
void Mision::setFechaLlegada(QDate f) { fecha_llegada = f; }
void Mision::setEtapas(QJsonObject e) { etapas = e; }
