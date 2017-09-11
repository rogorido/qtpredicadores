#ifndef DIOCESIS_H
#define DIOCESIS_H

#include <QString>
#include <QJsonObject>

class Diocesis
{
public:
    Diocesis();

    // setters
    void setId(int i);
    void setNombre(QString n);
    void setNombreLatin(QString n);
    void setArchidiosis(bool a);
    void setSufraganea(int s);
    void setLugar(int l);
    void setExistente(bool e);
    void setInfidelibus(bool i);
    void setMotivoDesaparicion(QString m);
    void setOtrosDatos(QJsonObject o);

    // getters
    int getId() const { return id; }
    QString getNombre() const { return nombre; }
    QString getNombreLatin() const { return nombre_latin; }
    bool getArchidiocesis() const { return archidiocesis; }
    int getSufraganea() const { return sufraganeade; } // devuelve el id de la diócesis de la que es sufragánea
    int getLugar() const { return lugar; }
    bool getExisteHoy() const { return existe_hoy; }
    bool getInfidelibus() const { return infidelibus; }
    QString getMotivoDesaparicion() const { return motivo_desaparicion; }
    QJsonObject getOtrosDatos() const{ return otros_datos; }

private:

    int id;
    QString nombre;
    QString nombre_latin;
    bool archidiocesis;
    int sufraganeade;
    int lugar;
    bool existe_hoy;
    bool infidelibus;
    QString motivo_desaparicion;
    QJsonObject otros_datos;

};

#endif // DIOCESIS_H
