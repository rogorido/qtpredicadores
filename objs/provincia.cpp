#include "provincia.h"

Provincia::Provincia() { lleno = false; }

void Provincia::setId(const int i)
{
    id = i;
    lleno = true;
}
void Provincia::setNombre(const QString n)
{
    nombre = n;
    lleno = true;
}
void Provincia::setOtrosNombres(const QString o) { otrosnombres = o; }
void Provincia::setErigida(const QString e) { erigida = e; }
void Provincia::setNotas(const QString n) { notas = n; }
