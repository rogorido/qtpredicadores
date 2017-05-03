#include "pena.h"

Pena::Pena() { lleno = false; }

void Pena::setPenasTipos(QStringList p)
{
    penas_tipos = p;
    lleno = true;
}

void Pena::setPenaTexto(QString p) { pena_texto = p; }
void Pena::setDuracion(QString d) { duracion = d; }
void Pena::setRestriccion(QString r) { restriccion = r; }
void Pena::setAbsolucion(QString a) { absolucion = a; }
void Pena::setPenados(QStringList p)
{
    penados = p;
    lleno = true;
}
void Pena::setMotivo(QString m) { motivo = m; }
void Pena::setSeguridad(int s) { seguridad = s; }
void Pena::setExtraInfos(ExtraInfos e) { extras = e; }
