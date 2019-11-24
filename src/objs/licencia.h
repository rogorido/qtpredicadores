#ifndef LICENCIA_H
#define LICENCIA_H

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QStringList>

#include "notas.h"
#include "variados.h"

class Licencia {
 public:
  Licencia();

  // setters
  void setLicenciaTipo(const QString l);
  void setOtorgantes(const QStringList o);
  void setReceptores(const QStringList r);
  void setAsunto(const QString a);
  void setSeguridad(const int s);
  void setProvincia(const int p);
  void setCasa(const int c);
  void setExtraInfos(const ExtraInfos e);
  void setNotas(const Notas n);

  // getters
  QString getLicenciatipo() const { return licenciatipo; }
  QStringList getOtorgantes() const { return otorgantes; }
  QStringList getReceptores() const { return receptores; }
  QString getAsunto() const { return asunto; }
  int getSeguridad() const { return seguridad; }
  int getProvincia() const { return provincia; }
  int getCasa() const { return casa; }
  ExtraInfos getExtraInfos() const { return extras; }
  Notas getNotas() const { return nota; }

  QJsonObject getLicenciaJson();

 private:
  QString licenciatipo;
  QStringList otorgantes;
  QStringList receptores;
  QString asunto;
  int seguridad;  // de la interpretación
  int provincia;
  int casa;
  ExtraInfos extras;
  Notas nota;
};

#endif  // LICENCIA_H
