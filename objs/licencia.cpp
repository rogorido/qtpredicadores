#include "licencia.h"

Licencia::Licencia() { }

void Licencia::setLicenciaTipo(QString l) { licenciatipo = l; }
void Licencia::setOtorgantes(QStringList o) { otorgantes = o; }
void Licencia::setReceptores(QStringList r) { receptores = r; }
void Licencia::setAsunto(QString a) { asunto = a; }
void Licencia::setSeguridad(int s) { seguridad = s; }
void Licencia::setProvincia(int p) { provincia = p; }
void Licencia::setCasa(int c) { casa = c; }
void Licencia::setExtraInfos(ExtraInfos e) { extras = e; }
void Licencia::setNotas(Notas n) { nota = n; }

QJsonObject Licencia::getLicenciaJson()
{
    QJsonObject json;

    json.insert("licencia", "yes");

    if (!licenciatipo.isEmpty())
        json.insert("licencia_tipo", licenciatipo);

    if (!otorgantes.isEmpty())
        json.insert("licencia_otorgantes", QJsonArray::fromStringList(otorgantes));

    if (!receptores.isEmpty())
        json.insert("licencia_receptores", QJsonArray::fromStringList(receptores));

    if (!asunto.isEmpty())
        json.insert("licencia_asunto", asunto);

    json.insert("seguridad", QJsonValue(seguridad));

    if (provincia != 0)
        json.insert("provincia", provincia);

    if (casa != 0)
        json.insert("casa", casa);

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

