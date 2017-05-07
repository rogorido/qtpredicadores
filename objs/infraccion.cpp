#include "infraccion.h"

Infraccion::Infraccion() { }

void Infraccion::setTipo(QString t) {
    tipo = t;
    lleno = true;
}

void Infraccion::setInfraccion(QString i) {
    infraccion = i;
    lleno = true;
}

void Infraccion::setInfractores(QStringList i){
    infractores = i;
}

void Infraccion::setNota(Notas n) { nota = n; }
void Infraccion::setExtras(ExtraInfos e) { extras = e; }

QJsonObject Infraccion::getInfraccionJson(){
    QJsonObject json;

    return json;

}
