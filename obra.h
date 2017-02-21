#ifndef OBRA_H
#define OBRA_H

#include <QString>

// no lo derivo de QObject, por lo que no tiene ni signals ni slots

class Obra
{
public:
    Obra();

    // setters
    void setTitulo(QString t);
    void setIdioma(QString i);
    void setAutor(int a);
    void setTipo(QString t);
    void setFormato(QString f);
    void setTomos(int t);
    void setNumeroPags(QString np);
    void setImpreso(bool i);
    void setTalVezImpreso(bool i);
    void setManuscrito(bool m);
    void setLugarOriginal(QString l);
    void setLugar(int l);
    void setFecha(QString f);
    void setEditor(QString e);
    void setReferencias(bool r);
    void setTituloReducido(bool t);
    void setContenido(bool c);
    void setInteresante(int i);
    void setDudoso(bool d);
    void setFiabilidad(int f);
    void setNotas(QString n);

    //getters
    QString getTitulo() {return titulo;}
    QString getIdioma() {return idioma;}
    int getAutor() {return autor;}
    QString getTipo() {return tipo;}
    QString getFormato() {return formato;}
    int getTomos() {return tomos;}
    QString getNumeroPags() {return numeropags;}
    bool getImpreso() {return impreso;}
    bool getTalVezImpreso() {return talvez_impreso;}
    bool getManuscrito() {return manuscrito;}
    QString getLugarOriginal() {return lugaroriginal;}
    int getLugar() {return lugar;}
    QString getFecha() {return fecha;}
    QString getEditor() {return editor;}
    bool getReferencias() {return refs;}
    bool getTituloReducido() {return tituloreducido;}
    bool getContenido() {return contenido;}
    int getInteresante() {return interesante;}
    bool getDudoso() {return dudoso;}
    int getFiabilidad() {return fiabilidad;}
    QString getNotas() {return notas;}

private:

    QString titulo;
    QString idioma;
    int autor;
    QString tipo;
    QString formato;
    int tomos;
    QString numeropags;
    bool impreso;
    bool talvez_impreso;
    bool manuscrito;
    QString lugaroriginal;
    int lugar;
    QString fecha;
    QString editor;
    bool refs;
    bool tituloreducido;
    bool contenido;
    int interesante;
    bool dudoso;
    int fiabilidad;
    QString notas;

};

#endif // OBRA_H
