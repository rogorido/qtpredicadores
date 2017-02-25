#include "casa.h"

Casa::Casa()
{

}

void Casa::setNombre(QString n){
    if (!n.isEmpty())
        nombre = n;
}

void Casa::setLugar(int l){
    lugar = l;
}

void Casa::setBuscado(bool b){
    buscado = b;
}

void Casa::setStudiumgenerale(bool b){
    studiumgenerale = b;
}

void Casa::setWiki(bool w){
    wiki = w;
}

void Casa::setOtrosnombres(QString o){
    otrosnombres = o;
}

void Casa::setNotas(QString n){
    notas = n;
}
