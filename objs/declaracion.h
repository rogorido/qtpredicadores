#ifndef DECLARACION_H
#define DECLARACION_H

#include <QString>
#include <QJsonObject>

#include "objs/infraccion.h"
#include "objs/pena.h"
#include "objs/notas.h"
#include "objs/persona.h"

class Declaracion
{
public:
    Declaracion();

    void setTipo(QString t);
    void setInfraccion(Infraccion i);
    void setPena(Pena p);
    void setPersona(Persona p);
    void setNota(Notas n);
    void setExtraInfos(ExtraInfos e);
    void setExtraJson(QJsonObject e);

    // getters
    QString getTipo() const {return tipo;}
    Infraccion getInfraccion() const {return infraccion;}
    Pena getPena() const {return pena;}
    Persona getPersona() const {return persona;}
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

    // por qué coño tengo estos dos?
    ExtraInfos extras;
    QJsonObject extrajson; // esto casi debería ser una QList<QJsonObject>...

};

#endif // DECLARACION_H
