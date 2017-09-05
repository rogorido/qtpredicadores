#ifndef APROBACION_H
#define APROBACION_H

#include <QString>
#include <QJsonObject>

#include "objs/variados.h"
#include "objs/persona.h"
#include "objs/provincia.h"
#include "objs/casa.h"

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
    void setTipoInstitucion(QString t);
    void setPersona(Persona p);
    void setCasa(Casa c);
    void setProvincia(Provincia p);
    void setExtraInfos(ExtraInfos e);

    //getters
    TipoAprobacion getTipoAprobacion() const { return tipo_aprobacion; }
    QString getCargo() const { return cargo; }
    QString getTipoInstitucion() const { return tipo_institucion; }
    Persona getPersona() const { return persona; }
    Casa getCasa() const { return casa; }
    Provincia getProvincia() const { return provincia; }
    ExtraInfos getExtraInfos() const { return extras; }

    QJsonObject getAprobacionJson();

private:
    TipoAprobacion tipo_aprobacion;
    QString cargo;
    QString tipo_institucion;
    Persona persona;
    Casa casa;
    Provincia provincia;
    ExtraInfos extras;

};

#endif // APROBACION_H
