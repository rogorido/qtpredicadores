#ifndef RESOLUCION_H
#define RESOLUCION_H

#include <QString>

// no lo derivo de QObject, por lo que no tiene ni signals ni slots

class Resolucion
{
public:
    Resolucion();

    // setters
    void setId(int i);
    void setTexto(QString t);
    void setTextoTraducido(QString t);
    void setTextoResumido(QString t);
    void setCapitulo(int c);
    void setEpigrafe(QString e);
    void setProvincia(int p);
    void setEntendido(bool e);
    void setVolverMirar(bool v); 
    void setTraducido(bool t);
    void setInteres(int i);
    void setResolucionAnterior(int r);
    void setNotas(QString n);

    //getters
    int getId() const {return id;}
    QString getTexto() const {return texto;}
    QString getTextoTraducido() const {return texto_traducido;}
    QString getTextoResumido() const {return texto_resumido;}
    int getCapitulo() const {return capitulo;}
    QString getEpigrafe() const {return epigrafe;}
    int getProvincia() const {return provincia;}
    bool getEntendido() const {return entendido;}
    bool getVolverMirar() const {return volveramirar;}
    bool getTraducido() const {return traducido;}
    int getInteres() const {return interes;}
    int getResolucionAnterior() const {return resolucion_anterior;}
    QString getNotas() const {return notas;}
    
private:

    int id;
    QString texto;
    QString texto_traducido;
    QString texto_resumido;
    int capitulo;
    QString epigrafe;
    int provincia;
    bool entendido;
    bool volveramirar;
    bool traducido;
    int interes;
    int resolucion_anterior;
    QString notas;

};

#endif // RESOLUCION_H
