#ifndef CASA_H
#define CASA_H

#include <QString>

// no lo derivo de QObject, por lo que no tiene ni signals ni slots

class Casa {
 public:
  Casa();

  enum CamposCasa {
    ID = 0,
    NOMBRE,
    LATINNAME,
    OTHERNAMES,
    PLACEID,
    ORIGINALPLACE,
    MEN,
    TYPEHOUSE,
    CONGREGATION,
    STUDIUMGENERALE,
    WIKIPEDIA,
    LOOKEDUP,
    PROVINCEID,
    DIOCESE,
    DATEFOUNDATION,
    ADVOCATION,
    NOTES,
    DATEINSERTION,
    QUETIF,
    OTHERDATA,
    DATEELIMINATION
  };

  // setters
  void setId(const int i);
  void setNombre(const QString n);
  void setNombreLatin(const QString n);
  void setLugar(const int l);
  void setLugarOriginario(const QString n);
  void setMasculino(const bool m);
  void setTipo(const QString t);
  void setCongregacion(const QString c);
  void setBuscado(const bool b);
  void setWiki(const bool w);
  void setProvincia(const int p);
  void setDiocesis(const QString d);
  void setFechaFundacion(const QString f);
  void setFechaEliminacion(const QString f);
  void setAdvocacion(const QString a);
  void setQuetif(const bool q);
  void setStudiumgenerale(const bool w);
  void setOtrosnombres(const QString o);
  void setNotas(const QString n);
  void setOtrosDatos(const QString o);

  // getters
  int getId() const { return id; }
  QString getNombre() const { return nombre; }
  QString getNombreLatin() const { return nombre_latin; }
  int getLugar() const { return lugar; }
  QString getLugarOriginario() const { return lugar_originario; }
  bool getMasculino() const { return masculino; }
  QString getTipo() const { return tipo; }
  QString getCongregacion() const { return congregacion; }
  bool getBuscado() const { return buscado; }
  bool getWiki() const { return wiki; }
  int getProvincia() const { return provincia; }
  QString getDiocesis() const { return diocesis; }
  QString getFechaFundacion() const { return fecha_fundacion; }
  QString getFechaEliminacion() const { return fecha_elimacion; }
  QString getAdvocacion() const { return advocacion; }
  bool getQuetif() const { return quetif; }
  QString getOtrosNombres() const { return otrosnombres; }
  QString getNotas() const { return notas; }
  bool getStudiumgenerale() const { return studiumgenerale; }
  QString getOtrosDatos() const { return otrosdatos; }
  bool estaLleno() const { return lleno; }

 private:
  int id;
  QString nombre;
  QString nombre_latin;
  int lugar;
  QString lugar_originario;
  bool masculino;
  QString tipo;
  QString congregacion;
  bool buscado;
  bool wiki;
  int provincia;
  QString diocesis;
  QString fecha_fundacion;
  QString fecha_elimacion;
  QString advocacion;
  bool quetif;
  // este  sería interesante hacerlo con QJson...
  QString otrosnombres;
  QString notas;
  bool studiumgenerale;
  QString otrosdatos;  // aquí en principio va lo de fuentes
  bool lleno = false;
};

#endif  // CASA_H
