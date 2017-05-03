#include "provincia.h"

Provincia::Provincia() { lleno = false; }

void Provincia::setId(int i)
{
    id = i;
    lleno = true;
}
void Provincia::setNombre(QString n)
{
    nombre = n;
    lleno = true;
}
void Provincia::setOtrosNombres(QString o) { otrosnombres = o; }
void Provincia::setErigida(QString e) { erigida = e; }
void Provincia::setNotas(QString n) { notas = n; }
