#include "diocesis.h"

Diocesis::Diocesis()
{ }

void Diocesis::setId(const int i) { id = i; }
void Diocesis::setNombre(const QString n) { nombre = n; }
void Diocesis::setNombreLatin(const QString n) { nombre_latin = n; }
void Diocesis::setArchidiosis(const bool a) { archidiocesis = a; }
void Diocesis::setSufraganea(const int s) { sufraganeade = s; }
void Diocesis::setLugar(const int l) { lugar = l; }
void Diocesis::setExistente(const bool e) { existe_hoy = e; }
void Diocesis::setInfidelibus(const bool i) { infidelibus = i; }
void Diocesis::setTitularSee(const bool t) { titular_see = t; }
void Diocesis::setMotivoDesaparicion(const QString m) { motivo_desaparicion = m; }
void Diocesis::setNota(const Notas n) { nota = n; }
void Diocesis::setOtrosDatos(const QJsonObject o) { otros_datos = o; }
void Diocesis::setBuscadosTodosObispos(const bool b) { buscadosTodosObispos = b; }
void Diocesis::setSantaSede(const bool s) { santa_sede = s; }
void Diocesis::setUrlHierarchy(const QString u) { url_hierarchy = u; }

bool Diocesis::estaLleno()
{
    return nombre.isEmpty();
}
