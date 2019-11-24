#ifndef ORDENANZA_H
#define ORDENANZA_H

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QStringList>

#include "notas.h"
#include "pena.h"
#include "retroreferencia.h"
#include "variados.h"

class Ordenanza {
 public:
  Ordenanza();

  enum class TipoOrdenanza { MANDATO, PROHIBICION, ADMONICION, COMISION };

  // setters
  void setTipo(const TipoOrdenanza t);
  void setReceptores(const QStringList r);
  void setObjetos(const QStringList o);
  void setPena(const Pena p);
  void setRestriccion(const QString r);
  void setFinalidades(const QStringList f);
  void setSeguridad(const int s);
  void setRetroReferencia(const RetroReferencia r);
  void setTemas(const QList<int> t);
  void setExtraInfos(const ExtraInfos e);
  void setNota(const Notas n);

  // getters
  TipoOrdenanza getTipo() const { return tipo_ordenanza; }
  QStringList getReceptores() const { return receptores; }
  QStringList getObjetos() const { return objetos; }
  Pena getPena() const { return pena; }
  QString getRestriccion() const { return restriccion; }
  QStringList getFinalidades() const { return finalidades; }
  int getSeguridad() const { return seguridad; }
  RetroReferencia getRetroReferencia() const { return retro; }
  QList<int> getTemas() const { return temas; }
  ExtraInfos getExtraInfos() const { return extras; }
  Notas getNota() const { return nota; }

  QJsonObject getOrdenanzaJson();

 private:
  TipoOrdenanza tipo_ordenanza;
  QStringList receptores;
  QStringList objetos;
  Pena pena;
  QString restriccion;
  QStringList finalidades;  // no sé si lo voy a usar
  int seguridad;
  RetroReferencia retro;
  QList<int> temas;
  ExtraInfos extras;
  Notas nota;  // realmente lo es una...
};

#endif  // ORDENANZA_H
