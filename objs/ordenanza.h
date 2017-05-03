#ifndef ORDENANZA_H
#define ORDENANZA_H

#include <QString>
#include <QStringList>
#include <objs/pena.h>
#include <objs/variados.h>

class Ordenanza
{
public:
    Ordenanza();

    enum class TipoOrdenanza { MANDATO, PROHIBICION };

    // setters
    void setTipo(TipoOrdenanza t);
    void setReceptores(QStringList r);
    void setObjetos(QStringList o);
    void setPena(Pena p);
    void setRestriccion(QString r);
    void setFinalidades(QStringList f);
    void setSeguridad(int s);
    void setExtraInfos(ExtraInfos e);

    // getters
    TipoOrdenanza getTipo() const {return tipo_ordenanza;}
    QStringList getReceptores() const {return receptores;}
    QStringList getObjetos() const {return objetos;}
    Pena getPena() const {return pena;}
    QString getRestriccion() const {return restriccion;}
    QStringList getFinalidades() const {return finalidades;}
    int getSeguridad() const {return seguridad;}
    ExtraInfos getExtraInfos() const {return extras;}

private:

    TipoOrdenanza tipo_ordenanza;
    QStringList receptores;
    QStringList objetos;
    Pena pena;
    QString restriccion;
    QStringList finalidades; // no sé si lo voy a usar
    int seguridad;
    ExtraInfos extras;
};

#endif // ORDENANZA_H
