#ifndef VIAJE_H
#define VIAJE_H

#include <QString>
#include <QDate>

#include "objs/notas.h"

class QJsonObject;

class Viaje
{
public:
    Viaje();

    // setters
    void setOriginal(bool o);
    void setOrigen(int o);
    void setDestino(int d);
    void setMotivos(QStringList m);
    void setDuracion(int d);
    void setMuerto(bool m);
    void setMotivoMuerte(QString m);
    void setLugarMuerte(QString l);
    void setFechaInicio(QDate f);
    void setFechaFin(QDate f);
    void setNotas(Notas n);

    // getters
    bool getOriginal() const { return original; }
    int getOrigen() const { return origen; }
    int getDestino() const { return destino; }
    QStringList getMotivos() const { return motivos; }
    int getDuracion() const { return duracion; }
    bool getMuerto() const {return muerto; }
    QString getMotivoMuerte() const { return motivo_muerte; }
    QString getLugarMuerte() const { return lugar_muerte; }
    QDate getFechaInicio() const { return fecha_inicio; }
    QDate getFechaFin() const { return fecha_inicio; }
    Notas getNotas() const { return nota; }

    QJsonObject getViajeJson();

private:

    bool original;
    int origen;
    int destino;
    QStringList motivos;
    int duracion;
    bool muerto;
    QString motivo_muerte;
    QString lugar_muerte;
    QDate fecha_inicio;
    QDate fecha_fin;
    Notas nota;

};

#endif // VIAJE_H
