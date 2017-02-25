#ifndef PROVINCIA_H
#define PROVINCIA_H

#include <QString>

class Provincia
{
public:
    Provincia();

    void setId(int i);
    void setNombre(QString n);
    void setOtrosNombres(QString o);
    void setErigida(QString e);
    void setNotas(QString n);

    //getters
    int getId() const {return id;}
    QString getNombre() const {return nombre;}
    QString getOtrosNombres() const {return otrosnombres;}
    QString getErigida() const {return erigida;}
    QString getNotas() const {return notas;}

private:

    int id;
    QString nombre;
    QString otrosnombres;
    QString erigida;
    QString notas;

};

#endif // PROVINCIA_H
