#include "infraccion.h"

Infraccion::Infraccion() { }

void Infraccion::setTipo(const QString t) {
    tipo = t;
    lleno = true;
}

void Infraccion::setInfraccion(const QString i) {
    infraccion = i;
    lleno = true;
}

void Infraccion::setInfractores(const QStringList i){
    infractores = i;
}

void Infraccion::setNota(const Notas n) { nota = n; }
void Infraccion::setExtras(const ExtraInfos e) { extras = e; }

QJsonObject Infraccion::getInfraccionJson(){
    QJsonObject json;

    json.insert("infraccion", "yes");

    if (!tipo.isEmpty())
        json.insert("infraccion_tipo", tipo);

    if (!infraccion.isEmpty())
        json.insert("infraccion_asunto", infraccion);

    if (!infractores.isEmpty())
        json.insert("infraccion_infractores", QJsonArray::fromStringList(infractores));

    if (extras.size() > 0 ) {
        for (int i = 0; i < extras.size(); ++i) {
            QPair<QString, QString> valores;
            valores = extras.at(i);

            json.insert(valores.first, valores.second);
        }
    }

    if (nota.estaLleno()){
        json.insert("meta_info", nota.getNotasJson());
    }

    return json;

}
