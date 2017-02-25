#ifndef PERSONA_H
#define PERSONA_H

#include <QString>

// no lo derivo de QObject, por lo que no tiene ni signals ni slots

class Persona
{
public:
    Persona();

    // setters
    void setId(int i);
    void setNombre(QString n);
    void setApellidos(QString a);
    void setBuscado(bool b);
    void setWiki(bool w);
    void setViaf(bool v);
    void setWikilink(QString wl);
    void setViaflink(QString vl);
    void setNacimiento(QString nac);
    void setMuerte(QString m);
    void setOtrosnombres(QString o);
    void setOtrosdatos(QString o);
    void setNotas(QString n);

    //getters
    int getId() const {return id;}
    QString getNombre() const {return nombre;}
    QString getApellidos() const {return apellidos;}
    bool getBuscado() const {return buscado;}
    bool getWiki() const {return wiki;}
    bool getViaf() const {return viaf;}
    QString getWikilink() const {return wikilink;}
    QString getViaflink() const {return viaflink;}
    QString getNacimiento() const {return nacimiento;}
    QString getMuerte() const {return muerte;}
    QString getOtrosNombres() const {return otrosnombres;}
    QString getOtrosDatos() const {return otrosdatos;}
    QString getNotas() const {return notas;}

private:

    int id;
    QString nombre;
    QString apellidos;
    bool buscado;
    bool wiki;
    bool viaf;
    QString wikilink;
    QString viaflink;
    QString nacimiento;
    QString muerte;
    // estos dos sería interesantes hacerlos QJson...
    QString otrosnombres;
    QString otrosdatos;
    QString notas;

};

#endif // PERSONA_H
