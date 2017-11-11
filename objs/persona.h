#ifndef PERSONA_H
#define PERSONA_H

#include <QString>

#include "objs/variados.h"

// no lo derivo de QObject, por lo que no tiene ni signals ni slots

class Persona
{
public:
    Persona();

    // setters
    void setId(int i);
    void setNombre(QString n);
    void setApellidos(QString a);
    void setOrigen(QString o);
    void setMasculino(bool m);
    void setBuscado(bool b);
    void setWiki(bool w);
    void setViaf(bool v);
    void setTipoPersona(QString t);
    void setWikilink(QString wl);
    void setViaflink(QString vl);
    void setWikidata(QString w);
    void setNacimiento(QString nac);
    void setMuerte(QString m);
    void setDiocesis(QString d);
    void setOtrosnombres(QString o);
    void setOtrosdatos(QString o);
    void setVolverMirar(bool v);
    void setCantidadInfo(int c);
    void setNotas(QString n);
    void setFuente(fuente f);

    //getters
    int getId() const { return id; }
    QString getNombre() const { return nombre; }
    QString getApellidos() const { return apellidos; }
    QString getOrigen() const { return origen; }
    bool getMasculino() const { return masculino; }
    bool getBuscado() const { return buscado; }
    bool getWiki() const { return wiki; }
    bool getViaf() const { return viaf; }
    QString getTipoPersona() const { return tipo_persona; }
    QString getWikilink() const { return wikilink; }
    QString getViaflink() const { return viaflink; }
    QString getWikidata() const { return wikidata; }
    QString getNacimiento() const { return nacimiento; }
    QString getMuerte() const { return muerte; }
    QString getDiocesis() const { return diocesis; }
    QString getOtrosNombres() const { return otrosnombres; }
    QString getOtrosDatos() const { return otrosdatos; }
    bool getVolverMirar() const { return volveramirar; }
    int getCantidadInfo() const { return cantidadinfo; }
    QString getNotas() const { return notas; }
    fuente getFuente() const { return fuente_origen; }
    bool estaLleno() const { return lleno; }

    // esto es para facilitar el mostrar nombre apellidos, etc. en formularios
    QString getNombreCompleto() const;

private:

    int id;
    QString nombre;
    QString apellidos;
    QString origen;
    bool masculino;
    bool buscado;
    bool wiki;
    bool viaf;
    QString tipo_persona;
    QString wikilink;
    QString viaflink;
    QString wikidata;
    QString nacimiento;
    QString muerte;
    QString diocesis;
    // estos dos sería interesantes hacerlos QJson...
    QString otrosnombres;
    QString otrosdatos;
    bool volveramirar;
    int cantidadinfo;
    QString notas;
    fuente fuente_origen;
    bool lleno = false;

};

#endif // PERSONA_H
