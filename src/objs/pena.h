#ifndef PENA_H
#define PENA_H

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QStringList>

#include "notas.h"
#include "variados.h"

class Pena {
 public:
  Pena();

  // setters
  void setPenasTipos(const QStringList p);
  void setPenaTexto(const QString p);
  void setDuracion(const QString d);
  void setRestriccion(const QString r);
  void setAbsolucion(const QString a);
  void setPenados(const QStringList p);
  void setMotivo(const QString m);
  void setExtraInfos(const ExtraInfos e);
  void setNotas(const Notas n);

  // getters
  QStringList getPenasTipos() const { return penas_tipos; }
  QString getPenaTexto() const { return pena_texto; }
  QString getDuracion() const { return duracion; }
  QString getRestriccion() const { return restriccion; }
  QString getAbsolucion() const { return absolucion; }
  QStringList getPenados() const { return penados; }
  QString getMotivo() const { return motivo; }
  ExtraInfos getExtraInfos() const { return extras; }
  Notas getNotas() const { return nota; }
  bool estaLleno() const { return lleno; }

  QJsonObject getPenaJson();

 private:
  QStringList penas_tipos;
  QString pena_texto;
  QString duracion;
  QString restriccion;
  QString absolucion;  // quién puede absolver
  QStringList penados;
  QString motivo;
  ExtraInfos extras;
  Notas nota;
  bool lleno = false;
};

#endif  // PENA_H
