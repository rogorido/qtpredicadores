#ifndef ORDENANZA_H
#define ORDENANZA_H

#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>

#include "objs/pena.h"
#include "objs/variados.h"
#include "objs/retroreferencia.h"

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
    void setRetroReferencia(RetroReferencia r);
    void setTemas(QList<int> t);
    void setExtraInfos(ExtraInfos e);

    // getters
    TipoOrdenanza getTipo() const {return tipo_ordenanza;}
    QStringList getReceptores() const {return receptores;}
    QStringList getObjetos() const {return objetos;}
    Pena getPena() const {return pena;}
    QString getRestriccion() const {return restriccion;}
    QStringList getFinalidades() const {return finalidades;}
    int getSeguridad() const {return seguridad;}
    RetroReferencia getRetroReferencia() const {return retro;}
    QList<int> getTemas() const {return temas;}
    ExtraInfos getExtraInfos() const {return extras;}

    QJsonObject getOrdenanzaJson();

private:

    TipoOrdenanza tipo_ordenanza;
    QStringList receptores;
    QStringList objetos;
    Pena pena;
    QString restriccion;
    QStringList finalidades; // no sé si lo voy a usar
    int seguridad;
    RetroReferencia retro;
    QList<int> temas;
    ExtraInfos extras;
};

#endif // ORDENANZA_H
