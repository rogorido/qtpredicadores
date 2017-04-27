#ifndef CAPITULO_H
#define CAPITULO_H

#include <QString>
#include <QDate>

// no lo derivo de QObject, por lo que no tiene ni signals ni slots

class Capitulo
{
public:
    Capitulo();

    // setters
    void setId(int id);
    void setNombre(QString nombre);
    void setLugar(int lugar);
    void setTipo(QString tipo);
    void setAsistentes(QString asistentes);
    void setVolumen(QString volumen);
    void setPaginas(QString paginas);
    void setNotas(QString notas);
    void setMaestroGeneral(int maestrogeneral);
    void setDefinitorio(bool d);
    void setFechaInicio(QDate f_inicio);
    void setFechaFin(QDate f_fin);

    //getters
    int getId() const {return id;}
    QString getNombre() const {return nombre;}
    int getLugar() const {return lugar;}
    QString getTipo() const {return tipo;}
    QString getAsistentes() const {return asistentes;}
    QString getVolumen() const {return volumen;}
    QString getPaginas() const {return paginas;}
    QString getNotas() const {return notas;}
    int getMaestroGeneral() const {return maestrogeneral;}
    bool getDefinitorio() const {return definitorio;}
    QDate getFechaInicio() const {return fecha_inicio;}
    QDate getFechaFin() const {return fecha_fin;}
    
private:

    int id;
    QString nombre;
    int lugar;
    QString tipo;
    QDate fecha_inicio;
    QDate fecha_fin;
    int maestrogeneral;
    bool definitorio;
    QString asistentes; 
    QString volumen;
    QString paginas;
    QString notas;
    // realmente falta un campo varia json pero
    // que no tengo todavía en el formulario 

};

#endif // CAPITULO_H
