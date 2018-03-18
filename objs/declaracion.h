#ifndef DECLARACION_H
#define DECLARACION_H

#include <QString>
#include <QJsonObject>

#include "objs/infraccion.h"
#include "objs/pena.h"
#include "objs/notas.h"
#include "objs/persona.h"
#include "objs/retroreferencia.h"

class Declaracion
{
public:
    Declaracion();

    void setTipo(const QString t);
    void setInfraccion(const Infraccion i);
    void setPena(const Pena p);
    void setPersona(const Persona p);
    void setCargos(const QStringList c);
    void setInstituciones(const QStringList i);
    void setProvincias(const QList<int> p);
    void setRetroReferencia(const RetroReferencia r);
    void setNota(const Notas n);
    void setExtraInfos(const ExtraInfos e);
    void setExtraJson(const QJsonObject e);

    // getters
    QString getTipo() const {return tipo;}
    Infraccion getInfraccion() const {return infraccion;}
    Pena getPena() const {return pena;}
    Persona getPersona() const {return persona;}
    QStringList getCargos() const {return cargos;}
    QStringList getInstituciones() const {return instituciones;}
    QList<int> getProvincias() const {return provincias;}
    RetroReferencia getRetroReferencia() const {return retro;}
    Notas getNota() const {return nota;}
    ExtraInfos getExtras() const {return extras;}
    QJsonObject getExtrajson() const {return extrajson;}

    QJsonObject getDeclaracionJson();

private:

    /*!
     * \brief Tipo de declaración
     *
     * Exactamente qué coño quería meter aquí?
     */
    QString tipo;

    /*!
     * \brief Infracción
     *
     * Se mete aquí el tipo de infracción, los infractores, etc.
     */
    Infraccion infraccion;

    /*!
     * \brief Pena
     *
     * Tipo de pena, etc. Pero cómo coño pienso conjugarlo esto
     * con lo anterior?
     */
    Pena pena;

    /*!
     * \brief persona
     *
     * Esto cómo va con lo anterior?
     */
    Persona persona; // tvz tendría que ser Qlist... o QList<int>
    Notas nota;

    /*
     *  estos son para cuando tengo una declaración de esas
     * muy ambigua y general
     */
    QStringList cargos;
    QStringList instituciones;
    QList<int> provincias;
    RetroReferencia retro;

    // por qué coño tengo estos dos?
    ExtraInfos extras;
    QJsonObject extrajson; // esto casi debería ser una QList<QJsonObject>...

};

#endif // DECLARACION_H
