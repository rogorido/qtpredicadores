#include "casa.h"

Casa::Casa() { lleno = false; }

void Casa::setId(const int i)
{
  id = i;
  lleno = true;
}

void Casa::setNombre(const QString n)
{
  if (!n.isEmpty()) {
    nombre = n;
    lleno = true;
  }
}

void Casa::setNombreLatin(const QString n)
{
  if (!n.isEmpty()) nombre_latin = n;
}

void Casa::setLugar(const int l) { lugar = l; }
void Casa::setLugarOriginario(const QString n) { lugar_originario = n; }
void Casa::setMasculino(const bool m) { masculino = m; }
void Casa::setTipo(const QString t) { tipo = t; }
void Casa::setCongregacion(const QString c) { congregacion = c; }
void Casa::setBuscado(const bool b) { buscado = b; }
void Casa::setStudiumgenerale(const bool b) { studiumgenerale = b; }
void Casa::setWiki(const bool w) { wiki = w; }
void Casa::setProvincia(const int p) { provincia = p; }
void Casa::setDiocesis(const QString d) { diocesis = d; }
void Casa::setFechaFundacion(const QString f) { fecha_fundacion = f; }
void Casa::setFechaEliminacion(const QString f) { fecha_elimacion = f; }
void Casa::setAdvocacion(const QString a) { advocacion = a; }
void Casa::setQuetif(const bool q) { quetif = q; }
void Casa::setOtrosnombres(const QString o) { otrosnombres = o; }
void Casa::setNotas(const QString n) { notas = n; }
void Casa::setOtrosDatos(const QString o) { otrosdatos = o; }
