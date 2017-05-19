#ifndef OBISPO_H
#define OBISPO_H

#include <QDate>
#include <QJsonObject>

class Obispo
{
public:
    Obispo();


    // getters
    int getId() const { return id; }
    int getPersona() const { return persona; }
    int getDiocesis() const { return diocesis; }
    int getPapa() const { return papa; }
    QDate getFechaNominacion() const { return fecha_nominacion; }
    QDate getFechaFin() const { return fecha_fin; }
    bool getCircaFecha() const { return circa_fecha; }
    QString getDuracion() const { return duracion; }
    bool getFinPorMuerte() const { return finpormuerte; }
    bool getVolverMirar() const { return volveramirar; }
    QJsonObject getOtrosDatos() const { return otros_datos; }

private:

    int id;
    int persona;
    int diocesis;
    int papa;
    QDate fecha_nominacion;
    QDate fecha_fin;
    bool circa_fecha; // el campo circa_date_nomination
    QString duracion;
    bool finpormuerte;
    bool volveramirar;
    QJsonObject otros_datos;

};

#endif // OBISPO_H
