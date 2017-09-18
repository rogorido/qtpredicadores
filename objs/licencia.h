#ifndef LICENCIA_H
#define LICENCIA_H

#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>

#include "objs/variados.h"
#include "objs/notas.h"

class Licencia
{
public:
    Licencia();

    // setters
    void setLicenciaTipo(QString l);
    void setOtorgantes(QStringList o);
    void setReceptores(QStringList r);
    void setAsunto(QString a);
    void setSeguridad(int s);
    void setProvincia(int p);
    void setCasa(int c);
    void setExtraInfos(ExtraInfos e);
    void setNotas(Notas n);

    // getters
    QString getLicenciatipo() const { return licenciatipo; }
    QStringList getOtorgantes() const { return otorgantes; }
    QStringList getReceptores() const { return receptores; }
    QString getAsunto() const { return asunto; }
    int getSeguridad() const { return seguridad; }
    int getProvincia() const { return provincia; }
    int getCasa() const { return casa; }
    ExtraInfos getExtraInfos() const { return extras; }
    Notas getNotas() const { return nota; }

    QJsonObject getLicenciaJson();

private:

    QString licenciatipo;
    QStringList otorgantes;
    QStringList receptores;
    QString asunto;
    int seguridad; // de la interpretación
    int provincia;
    int casa;
    ExtraInfos extras;
    Notas nota;

};

#endif // LICENCIA_H
