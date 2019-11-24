#ifndef LUGAR_H
#define LUGAR_H

#include <QString>

// no lo derivo de QObject, por lo que no tiene ni signals ni slots

class Lugar {
 public:
  Lugar();

  // setters
  void setId(const int i);
  void setLugar(const QString l);
  void setLugarLatin(const QString l);
  void setPais(const QString p);
  void setOtrosNombres(const QString o);
  void setWikidata(const QString w);
  void setTipoLugar(const QString t);

  // getters
  int getId() const { return id; }
  QString getLugar() const { return lugar; }
  QString getLugarLatin() const { return lugar_latin; }
  QString getPais() const { return pais; }
  QString getOtrosNombres() const { return otros_nombres; }
  QString getWikidata() const { return wikidata; }
  QString getTipoLugar() const { return tipo_lugar; }

 private:
  int id;
  QString lugar;
  QString lugar_latin;
  QString pais;
  QString otros_nombres;
  QString wikidata;
  QString tipo_lugar;
};

#endif  // LUGAR_H
