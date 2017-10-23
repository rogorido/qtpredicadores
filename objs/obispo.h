#ifndef OBISPO_H
#define OBISPO_H

#include <QDate>
#include <QJsonObject>

class Obispo
{
public:
    Obispo();

    // setters
    void setId(int i);
    void setPersona(int p);
    void setDiocesis(int d);
    void setPapa(int p);
    void setFechaNominacion(QDate f);
    void setFechaFin(QDate f);
    void setCircaFecha(bool c);
    void setDuracion(QString d);
    void setFinPorMuerte(bool f);
    void setVolverMirar(bool v);
    void setInGcatholic(bool i);
    void setSufraganeo(bool s);
    void setOtrosDatos(QJsonObject o);

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
    bool getInGcatholic() const { return en_gcatholic; }
    bool getSufraganeo() const { return sufraganeo; }
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
    bool en_gcatholic;
    bool sufraganeo;
    QJsonObject otros_datos;

};

#endif // OBISPO_H
