#ifndef CASA_H
#define CASA_H

#include <QString>

// no lo derivo de QObject, por lo que no tiene ni signals ni slots

class Casa
{
public:
    Casa();

    // setters
    void setId(int i);
    void setNombre(QString n);
    void setLugar(int l);
    void setBuscado(bool b);
    void setWiki(bool w);
    void setStudiumgenerale(bool w);
    void setOtrosnombres(QString o);
    void setNotas(QString n);

    //getters
    int getId() const {return id;}
    QString getNombre() const {return nombre;}
    int getLugar() const {return lugar;}
    bool getBuscado() const {return buscado;}
    bool getWiki() const {return wiki;}
    QString getOtrosNombres() const {return otrosnombres;}
    QString getNotas() const {return notas;}
    bool getStudiumgenerale() const {return studiumgenerale;}

private:

    int id;
    QString nombre;
    int lugar;
    bool buscado;
    bool wiki;
    // este  sería interesante hacerlo con QJson...
    QString otrosnombres;
    QString notas;
    bool studiumgenerale;

};

#endif // CASA_H
