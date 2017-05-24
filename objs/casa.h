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
    void setNombreLatin(QString n);
    void setLugar(int l);
    void setLugarOriginario(QString n);
    void setMasculino(bool m);
    void setTipo(QString t);
    void setCongregacion(QString c);
    void setBuscado(bool b);
    void setWiki(bool w);
    void setProvincia(int p);
    void setDiocesis(QString d);
    void setFechaFundacion(QString f);
    void setAdvocacion(QString a);
    void setQuetif(bool q);
    void setStudiumgenerale(bool w);
    void setOtrosnombres(QString o);
    void setNotas(QString n);
    void setOtrosDatos(QString o);

    //getters
    int getId() const {return id;}
    QString getNombre() const {return nombre;}
    QString getNombreLatin() const {return nombre_latin;}
    int getLugar() const {return lugar;}
    QString getLugarOriginario() const {return lugar_originario;}
    bool getMasculino() const {return masculino;}
    QString getTipo() const {return tipo;}
    QString getCongregacion() const {return congregacion;}
    bool getBuscado() const {return buscado;}
    bool getWiki() const {return wiki;}
    int getProvincia() const {return provincia;}
    QString getDiocesis() const {return diocesis;}
    QString getFechaFundacion() const {return fecha_fundacion;}
    QString getAdvocacion() const {return advocacion;}
    bool getQuetif() const {return quetif;}
    QString getOtrosNombres() const {return otrosnombres;}
    QString getNotas() const {return notas;}
    bool getStudiumgenerale() const {return studiumgenerale;}
    QString getOtrosDatos() const {return otrosdatos;}
    bool estaLleno() const {return lleno;}

private:

    int id;
    QString nombre;
    QString nombre_latin;
    int lugar;
    QString lugar_originario;
    bool masculino;
    QString tipo;
    QString congregacion;
    bool buscado;
    bool wiki;
    int provincia;
    QString diocesis;
    QString fecha_fundacion;
    QString advocacion;
    bool quetif;
    // este  sería interesante hacerlo con QJson...
    QString otrosnombres;
    QString notas;
    bool studiumgenerale;
    QString otrosdatos; // aquí en principio va lo de fuentes
    bool lleno = false;

};

#endif // CASA_H
