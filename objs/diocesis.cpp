#include "diocesis.h"

Diocesis::Diocesis()
{ }

void Diocesis::setId(int i) { id = i; }
void Diocesis::setNombre(QString n) { nombre = n; }
void Diocesis::setNombreLatin(QString n) { nombre_latin = n; }
void Diocesis::setArchidiosis(bool a) { archidiocesis = a; }
void Diocesis::setSufraganea(int s) { sufraganeade = s; }
void Diocesis::setLugar(int l) { lugar = l; }
void Diocesis::setExistente(bool e) { existe_hoy = e; }
void Diocesis::setInfidelibus(bool i) { infidelibus = i; }
void Diocesis::setTitularSee(bool t) { titular_see = t; }
void Diocesis::setMotivoDesaparicion(QString m) { motivo_desaparicion = m; }
void Diocesis::setNota(Notas n) { nota = n; }
void Diocesis::setOtrosDatos(QJsonObject o) { otros_datos = o; }
void Diocesis::setBuscadosTodosObispos(bool b) { buscadosTodosObispos = b; }
void Diocesis::setSantaSede(bool s) { santa_sede = s; }
void Diocesis::setUrlHierarchy(QString u) { url_hierarchy = u; }

bool Diocesis::estaLleno()
{
    return nombre.isEmpty();
}
