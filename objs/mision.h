#ifndef MISION_H
#define MISION_H

#include <QDate>
#include <QJsonObject>

class Mision
{
public:
    Mision();

    // setters
    void setId(int i);
    void setNumeroMision(int n);
    void setLugarSalida(int l);
    void setFechaSalida(QDate f);
    void setFechaLlegada(QDate f);
    void setEtapas(QString e);

    // getters
    int getId() const { return id; }
    int getNumeroMision() const { return numero_mision; }
    int getLugarSalida() const { return lugar_salida; }
    QDate getFechaSalida() const { return fecha_salida; }
    QDate getFechaLlegada() const { return fecha_llegada; }
    QString getEtapasJson() const { return etapas; }

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
};

#endif // MISION_H
