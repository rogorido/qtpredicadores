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
    void setOriginal(const bool o);
    void setOrigen(const int o);
    void setDestino(const int d);
    void setMotivos(const QStringList m);
    void setDuracion(const int d);
    void setVuelta(const bool v);
    void setMuerto(const bool m);
    void setMotivoMuerte(const QString m);
    void setLugarMuerte(const QString l);
    void setFechaInicio(const QDate f);
    void setFechaFin(const QDate f);
    void setNotas(const Notas n);

    // getters
    bool getOriginal() const { return original; }
    int getOrigen() const { return origen; }
    int getDestino() const { return destino; }
    QStringList getMotivos() const { return motivos; }
    int getDuracion() const { return duracion; }
    bool getVuelta() const { return vuelta; }
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
    bool vuelta;
    bool muerto;
    QString motivo_muerte;
    QString lugar_muerte;
    QDate fecha_inicio;
    QDate fecha_fin;
    Notas nota;

};

#endif // VIAJE_H
