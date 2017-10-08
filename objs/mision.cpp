#include "mision.h"

#include <QJsonDocument>

Mision::Mision() { }

void Mision::setId(int i) { id = i; }
void Mision::setNumeroMision(int n) { numero_mision = n; }
void Mision::setLugarSalida(int l) { lugar_salida = l; }
void Mision::setFechaSalida(QDate f){ fecha_salida = f; }
void Mision::setFechaLlegada(QDate f) { fecha_llegada = f; }
void Mision::setEtapas(QString e) { etapas = e; }
