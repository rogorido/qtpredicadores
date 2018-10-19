#include "obispo.h"

Obispo::Obispo()
{ }

void Obispo::setId(const int i) { id = i; }
void Obispo::setPersona(const int p) { persona = p; }
void Obispo::setPapa(const int p) { papa = p; }
void Obispo::setDiocesis(const int d) { diocesis = d; }
void Obispo::setFechaNominacion(const QDate f) { fecha_nominacion = f; }
void Obispo::setFechaFin(const QDate f) { fecha_fin= f; }
void Obispo::setCircaFecha(const bool c) { circa_fecha = c; }
void Obispo::setDuracion(const QString d) { duracion = d; }
void Obispo::setFinPorMuerte(const bool f) { finpormuerte = f; }
void Obispo::setVolverMirar(const bool v) { volveramirar = v; }
void Obispo::setInGcatholic(const bool i) { en_gcatholic = i; }
void Obispo::setSufraganeo(const bool s) { sufraganeo = s; }
void Obispo::setFinalRelativo(const bool f) { final_relativo = f; }
void Obispo::setOtrosDatos(const QJsonObject o) { otros_datos = o; }
