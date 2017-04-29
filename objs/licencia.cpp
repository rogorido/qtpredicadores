#include "licencia.h"

Licencia::Licencia() { }

void Licencia::setLicenciaTipo(QString l) { licenciatipo = l; }
void Licencia::setOtorgantes(QStringList o) { otorgantes = o; }
void Licencia::setReceptores(QStringList r) { receptores = r; }
void Licencia::setAsunto(QString a) { asunto = a; }
void Licencia::setSeguridad(int s) { seguridad = s; }
