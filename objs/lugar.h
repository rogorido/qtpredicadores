#ifndef LUGAR_H
#define LUGAR_H

#include <QString>

// no lo derivo de QObject, por lo que no tiene ni signals ni slots

class Lugar
{
public:
    Lugar();

    // setters
    void setId(int i);
    void setLugar(QString l);
    void setPais(QString p);

    //getters
    int getId() const {return id;}
    QString getLugar() const {return lugar;}
    QString getPais() const {return pais;}

private:

    int id;
    QString lugar;
    QString pais;

};

#endif // LUGAR_H
