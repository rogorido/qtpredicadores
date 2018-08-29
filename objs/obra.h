#ifndef OBRA_H
#define OBRA_H

#include <QString>

// no lo derivo de QObject, por lo que no tiene ni signals ni slots

class Obra
{
public:
    Obra();

    // NOTE: no entiendo por qué esto funciona como enum y no como enum class...
    enum CamposObra {
        ID = 0,
        TITLE,
        LANGUAGE_WORK,
        AUTHOR_ID,
        TYPE_WORK,
        FORMAT,
        VOLUMES,
        NUMBER_PAGES,
        PRINTED,
        MAYBE_PRINTED,
        MANUSCRIT,
        PLACE_PRINT_ORIGINAL,
        PLACE_PRINT_ID,
        DATE_PRINT,
        EDITOR,
        TRADUCTION,
        REFERENCES_WORK,
        REDUCED_TITLE,
        CONTENTS,
        INTERESTING,
        DUBIOUS,
        LOOK_AGAIN,
        EXPURGATABLE,
        RELIABILITY,
        NOTES,
        DATE_INSERTION,
        PAGE_QUETIF,
        INVESTIGATE
    };

    // setters
    void setTitulo(const QString t);
    void setIdioma(const QString i);
    void setAutor(const int a);
    void setTipo(const QString t);
    void setFormato(const QString f);
    void setTomos(const int t);
    void setNumeroPags(const QString np);
    void setImpreso(const bool i);
    void setTalVezImpreso(const bool i);
    void setManuscrito(const bool m);
    void setLugarOriginal(const QString l);
    void setLugar(const int l);
    void setFecha(const int f);
    void setEditor(const QString e);
    void setReferencias(const bool r);
    void setTituloReducido(const bool t);
    void setContenido(const bool c);
    void setInteresante(const int i);
    void setDudoso(const bool d);
    void setExpurgable(const bool e);
    void setFiabilidad(const int f);
    void setVolverMirar(const bool v);
    void setInvestigar(const bool i);
    void setTraduccion(const QString t);
    void setPageQuetif(const QString p);
    void setNotas(const QString n);

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
