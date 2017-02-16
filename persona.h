#ifndef PERSONA_H
#define PERSONA_H

#include <QString>

// no lo derivo de QObject, por lo que no tiene ni signals ni slots

class Persona
{
public:
    Persona();

    // setters
    void setNombre(QString n);
    void setApellidos(QString a);
    void setBuscado(bool b);
    void setWiki(bool w);
    void setViaf(bool v);
    void setWikilink(QString wl);
    void setViaflink(QString vl);
    void setNacimiento(QString nac);
    void setMuerte(QString m);

    //getters
    QString getNombre() const;
    QString getApellidos() const;
    bool getBuscado() const;
    bool getWiki() const;
    bool getViaf() const;
    QString getWikilink() const;
    QString getViaflink() const;
    QString getNacimiento() const;
    QString getMuerte() const;

private:

    QString nombre;
    QString apellidos;
    bool buscado;
    bool wiki;
    bool viaf;
    QString wikilink;
    QString viaflink;
    QString nacimiento;
    QString muerte;

};

#endif // PERSONA_H
