#include "casa.h"

Casa::Casa()
{  lleno = false; }

void Casa::setId(int i){
    id = i;
    lleno = true;
}

void Casa::setNombre(QString n){
    if (!n.isEmpty()){
        nombre = n;
        lleno = true;
    }
}

void Casa::setNombreLatin(QString n){
    if (!n.isEmpty())
        nombre_latin = n;
}

void Casa::setLugar(int l) { lugar = l; }
void Casa::setLugarOriginario(QString n) { lugar_originario = n; }
void Casa::setMasculino(bool m) { masculino = m; }
void Casa::setTipo(QString t) { tipo = t; }
void Casa::setCongregacion(QString c) { congregacion = c; }
void Casa::setBuscado(bool b) { buscado = b; }
void Casa::setStudiumgenerale(bool b) { studiumgenerale = b; }
void Casa::setWiki(bool w) { wiki = w; }
void Casa::setProvincia(int p) { provincia = p; }
void Casa::setDiocesis(QString d) { diocesis = d; }
void Casa::setFechaFundacion(QString f) { fecha_fundacion = f; }
void Casa::setAdvocacion(QString a) { advocacion = a; }
void Casa::setQuetif(bool q) { quetif = q; }
void Casa::setOtrosnombres(QString o) { otrosnombres = o; }
void Casa::setNotas(QString n) { notas = n; }
void Casa::setOtrosDatos(QString o) { otrosdatos = o; }
