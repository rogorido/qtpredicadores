#include "sufragio.h"

Sufragio::Sufragio()
{ }

void Sufragio::setTipo(QString t) { tipo = t;}
void Sufragio::setMisas(int m) { misas = m; }
void Sufragio::setMotivo(QString m) { motivo = m; }
void Sufragio::setDestinatarios(QStringList d) { destinatarios = d; }

QJsonObject Sufragio::getSufragio()
{
    QJsonObject json;

    json.insert("sufragio", "yes");

}
