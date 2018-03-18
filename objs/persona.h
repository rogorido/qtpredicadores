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
    void setId(const int i);
    void setNombre(const QString n);
    void setApellidos(const QString a);
    void setOrigen(const QString o);
    void setMasculino(const bool m);
    void setBuscado(const bool b);
    void setWiki(const bool w);
    void setViaf(const bool v);
    void setTipoPersona(const QString t);
    void setWikilink(const QString wl);
    void setViaflink(const QString vl);
    void setWikidata(const QString w);
    void setNacimiento(const QString nac);
    void setMuerte(const QString m);
    void setDiocesis(const QString d);
    void setOtrosnombres(const QString o);
    void setOtrosdatos(const QString o);
    void setVolverMirar(const bool v);
    void setCantidadInfo(const int c);
    void setNotas(const QString n);
    void setFuente(const fuente f);

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
