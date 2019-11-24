#ifndef DIOCESIS_H
#define DIOCESIS_H

#include <QJsonObject>
#include <QString>

#include "notas.h"

class Diocesis {
 public:
  Diocesis();

  // setters
  void setId(const int i);
  void setNombre(const QString n);
  void setNombreLatin(const QString n);
  void setArchidiosis(const bool a);
  void setSufraganea(const int s);
  void setLugar(const int l);
  void setExistente(const bool e);
  void setInfidelibus(const bool i);
  void setTitularSee(const bool t);
  void setMotivoDesaparicion(const QString m);
  void setNota(const Notas n);
  void setOtrosDatos(const QJsonObject o);
  void setBuscadosTodosObispos(const bool b);
  void setSantaSede(const bool s);
  void setUrlHierarchy(const QString u);

  // getters
  int getId() const { return id; }
  QString getNombre() const { return nombre; }
  QString getNombreLatin() const { return nombre_latin; }
  bool getArchidiocesis() const { return archidiocesis; }
  int getSufraganea() const
  {
    return sufraganeade;
  }  // devuelve el id de la diócesis de la que es sufragánea
  int getLugar() const { return lugar; }
  bool getExisteHoy() const { return existe_hoy; }
  bool getInfidelibus() const { return infidelibus; }
  bool getTitularSee() const { return titular_see; }
  QString getMotivoDesaparicion() const { return motivo_desaparicion; }
  Notas getNota() const { return nota; }
  QJsonObject getOtrosDatos() const { return otros_datos; }
  bool getBuscadosTodosObispos() const { return buscadosTodosObispos; }
  bool getSantaSede() const { return santa_sede; }
  QString getUrlHierarchy() const { return url_hierarchy; }

  bool estaLleno();

 private:
  int id;
  QString nombre;
  QString nombre_latin;
  bool archidiocesis;
  int sufraganeade;
  int lugar;
  bool existe_hoy;
  bool infidelibus;
  bool titular_see;
  QString motivo_desaparicion;
  Notas nota;
  QJsonObject otros_datos;
  bool buscadosTodosObispos;
  bool santa_sede;
  QString url_hierarchy;
};

#endif  // DIOCESIS_H
