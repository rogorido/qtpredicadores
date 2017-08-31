#include "obispo.h"

Obispo::Obispo()
{ }

void Obispo::setId(int i) { id = i; }
void Obispo::setPersona(int p) { persona = p; }
void Obispo::setPapa(int p) { papa = p; }
void Obispo::setDiocesis(int d) { diocesis = d; }
void Obispo::setFechaNominacion(QDate f) { fecha_nominacion = f; }
void Obispo::setFechaFin(QDate f) { fecha_fin= f; }
void Obispo::setCircaFecha(bool c) { circa_fecha = c; }
void Obispo::setDuracion(QString d) { duracion = d; }
void Obispo::setFinPorMuerte(bool f) { finpormuerte = f; }
void Obispo::setVolverMirar(bool v) { volveramirar = v; }
void Obispo::setOtrosDatos(QJsonObject o) { otros_datos = o; }