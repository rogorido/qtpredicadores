#ifndef OBISPO_H
#define OBISPO_H

#include <QDate>
#include <QJsonObject>

class Obispo {
 public:
  Obispo();

  // setters
  void setId(const int i);
  void setPersona(const int p);
  void setDiocesis(const int d);
  void setPapa(const int p);
  void setFechaNominacion(const QDate f);
  void setFechaFin(const QDate f);
  void setCircaFecha(const bool c);
  void setDuracion(const QString d);
  void setFinPorMuerte(const bool f);
  void setVolverMirar(const bool v);
  void setInGcatholic(const bool i);
  void setSufraganeo(const bool s);
  void setFinalRelativo(const bool f);
  void setOtrosDatos(const QJsonObject o);

  // getters
  int getId() const { return id; }
  int getPersona() const { return persona; }
  int getDiocesis() const { return diocesis; }
  int getPapa() const { return papa; }
  QDate getFechaNominacion() const { return fecha_nominacion; }
  QDate getFechaFin() const { return fecha_fin; }
  bool getCircaFecha() const { return circa_fecha; }
  QString getDuracion() const { return duracion; }
  bool getFinPorMuerte() const { return finpormuerte; }
  bool getVolverMirar() const { return volveramirar; }
  bool getInGcatholic() const { return en_gcatholic; }
  bool getSufraganeo() const { return sufraganeo; }
  bool getFinalRelativo() const { return final_relativo; }
  QJsonObject getOtrosDatos() const { return otros_datos; }

 private:
  int id;
  int persona;
  int diocesis;
  int papa;
  QDate fecha_nominacion;
  QDate fecha_fin;
  bool circa_fecha;  // el campo circa_date_nomination
  QString duracion;
  bool finpormuerte;
  bool volveramirar;
  bool en_gcatholic;
  bool sufraganeo;
  bool final_relativo;
  QJsonObject otros_datos;
};

#endif  // OBISPO_H
