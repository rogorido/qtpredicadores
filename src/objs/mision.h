#ifndef MISION_H
#define MISION_H

#include <QDate>
#include <QJsonObject>

#include "notas.h"

class Mision
{
public:
    Mision();

    // setters
    void setId(const int i);
    void setNumeroMision(const int n);
    void setLugarSalida(const int l);
    void setFechaSalida(const QDate f);
    void setFechaLlegada(const QDate f);
    void setEtapas(const QString e);
    void setNota(const Notas n);

    // getters
    int getId() const { return id; }
    int getNumeroMision() const { return numero_mision; }
    int getLugarSalida() const { return lugar_salida; }
    QDate getFechaSalida() const { return fecha_salida; }
    QDate getFechaLlegada() const { return fecha_llegada; }
    QString getEtapasJson() const { return etapas; }
    Notas getNota() const { return nota; }

private:

    int id;
    int numero_mision;
    int lugar_salida;
    QDate fecha_salida;
    QDate fecha_llegada;
    /*
     * esto está metido como json pero
     * lo operamos como un QString pq así es más fácil
     * usando el QJsonModel
     */
    QString etapas;
    Notas nota;
};

#endif // MISION_H
