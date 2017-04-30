#include "pena.h"

Pena::Pena() { }

void Pena::setPenasTipos(QStringList p) { penas_tipos = p; }
void Pena::setPenaTexto(QString p) { pena_texto = p; }
void Pena::setDuracion(QString d) { duracion = d; }
void Pena::setRestriccion(QString r) { restriccion = r; }
void Pena::setAbsolucion(QString a) { absolucion = a; }
void Pena::setPenados(QStringList p) { penados = p; }
void Pena::setMotivo(QString m) { motivo = m; }
void Pena::setSeguridad(int s) { seguridad = s; }
