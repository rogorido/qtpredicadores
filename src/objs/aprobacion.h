#ifndef APROBACION_H
#define APROBACION_H

#include <QJsonObject>
#include <QString>

#include "casa.h"
#include "notas.h"
#include "persona.h"
#include "provincia.h"
#include "variados.h"

/*!
 * \brief Aprobaciones de cargos, casas, etc.
 *
 * Esta clase sirve para guardar aprobaciones de personas para cargos,
 * de casas, de colegios, etc. en provincias, etc.
 */
class Aprobacion {
 public:
  Aprobacion();

  enum class TipoAprobacion { PERSONA, CASA };

  // setters
  void setTipoAprobacion(const TipoAprobacion t);
  void setCargo(const QString c);
  void setTipoInstitucion(const QString t);
  void setPersona(const Persona p);
  void setCasa(const Casa c);
  void setProvincia(const Provincia p);
  void setNotas(const Notas n);
  void setExtraInfos(const ExtraInfos e);

  // getters
  TipoAprobacion getTipoAprobacion() const { return tipo_aprobacion; }
  QString getCargo() const { return cargo; }
  QString getTipoInstitucion() const { return tipo_institucion; }
  Persona getPersona() const { return persona; }
  Casa getCasa() const { return casa; }
  Provincia getProvincia() const { return provincia; }
  Notas getNotas() const { return nota; }
  ExtraInfos getExtraInfos() const { return extras; }

  QJsonObject getAprobacionJson();

 private:
  TipoAprobacion tipo_aprobacion;
  QString cargo;
  QString tipo_institucion;
  Persona persona;
  Casa casa;
  Provincia provincia;
  Notas nota;
  ExtraInfos extras;
};

#endif  // APROBACION_H
