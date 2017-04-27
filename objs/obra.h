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
    void setFecha(int f);
    void setEditor(QString e);
    void setReferencias(bool r);
    void setTituloReducido(bool t);
    void setContenido(bool c);
    void setInteresante(int i);
    void setDudoso(bool d);
    void setExpurgable(bool e);
    void setFiabilidad(int f);
    void setVolverMirar(bool v);
    void setInvestigar(bool i);
    void setTraduccion(QString t);
    void setPageQuetif(QString p);
    void setNotas(QString n);

    //getters
    QString getTitulo() const {return titulo;}
    QString getIdioma() const {return idioma;}
    int getAutor() const {return autor;}
    QString getTipo() const {return tipo;}
    QString getFormato() const {return formato;}
    int getTomos() const {return tomos;}
    QString getNumeroPags() const {return numeropags;}
    bool getImpreso() const {return impreso;}
    bool getTalVezImpreso() const {return talvez_impreso;}
    bool getManuscrito() const {return manuscrito;}
    QString getLugarOriginal() const {return lugaroriginal;}
    int getLugar() const {return lugar;}
    int getFecha() const {return fecha;}
    QString getEditor() const {return editor;}
    bool getReferencias() const {return refs;}
    bool getTituloReducido() const {return tituloreducido;}
    bool getContenido() const {return contenido;}
    int getInteresante() const {return interesante;}
    bool getDudoso() const {return dudoso;}
    bool getExpurgable() const {return expurgable;}
    int getFiabilidad() const {return fiabilidad;}
    bool getVolverMirar() const {return volveramirar;}
    bool getInvestigar() const {return investigar;}
    QString getTraduccion() const {return traduccion;}
    QString getPageQuetif() const {return page_quetif;}
    QString getNotas() const {return notas;}

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
    int fecha;
    QString editor;
    bool refs;
    bool tituloreducido;
    bool contenido;
    int interesante;
    bool dudoso;
    bool expurgable;
    int fiabilidad;
    bool volveramirar;
    bool investigar;
    QString traduccion;
    QString page_quetif;
    QString notas;

};

#endif // OBRA_H
