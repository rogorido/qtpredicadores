#ifndef APROBACION_H
#define APROBACION_H

#include <QString>
#include <QJsonObject>

#include "objs/variados.h"
#include "objs/persona.h"
#include "objs/provincia.h"

/*!
 * \brief Aprobaciones de cargos, casas, etc.
 *
 * Esta clase sirve para guardar aprobaciones de personas para cargos,
 * de casas, de colegios, etc. en provincias, etc.
 */
class Aprobacion
{
public:
    Aprobacion();

    enum class TipoAprobacion { PERSONA, CASA };

    //setters
    void setTipoAprobacion(TipoAprobacion t);
    void setCargo(QString c);
    void setPersona(Persona p);
    void setProvincia(Provincia p);
    void setExtraInfos(ExtraInfos e);

    //getters
    TipoAprobacion getTipoAprobacion() const { return tipo_aprobacion; }
    QString getCargo() const {return cargo; }
    Persona getPersona() const {return persona; }
    Provincia getProvincia() const {return provincia; }
    ExtraInfos getExtraInfos() const { return extras; }

    QJsonObject getAprobacionJson();

private:
    TipoAprobacion tipo_aprobacion;
    QString cargo;
    Persona persona;
    Provincia provincia;
    ExtraInfos extras;

};

#endif // APROBACION_H
