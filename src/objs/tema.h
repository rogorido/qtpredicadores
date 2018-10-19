#ifndef TEMA_H
#define TEMA_H

#include <QString>

// no lo derivo de QObject, por lo que no tiene ni signals ni slots

class Tema
{
public:
    Tema();

    // setters
    void setId(const int id);
    void setTema(const QString n);
    void setSeleccionado(const bool s);

    //getters
    int getId() const {return id;}
    QString getTema() const {return tema;}
    bool getSeleccionado() const {return seleccionado;}
    
private:

    int id;
    QString tema;
    bool seleccionado;

};

#endif // TEMA_H
