#include "diocesis.h"

Diocesis::Diocesis()
{ }

void Diocesis::setId(int i) { id = i; }
void Diocesis::setNombre(QString n) { nombre = n; }
void Diocesis::setNombreLatin(QString n) { nombre_latin = n; }
void Diocesis::setArchidiosis(bool a) { archidiocesis = a; }
void Diocesis::setSufraganea(int s) { sufraganeade = s; }
void Diocesis::setExistente(bool e) { existe_hoy = e; }
void Diocesis::setOtrosDatos(QJsonObject o) { otros_datos = o; }
