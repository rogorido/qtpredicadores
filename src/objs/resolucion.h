#ifndef RESOLUCION_H
#define RESOLUCION_H

#include <QString>
#include <QStringList>

// no lo derivo de QObject, por lo que no tiene ni signals ni slots

class Resolucion {
 public:
  Resolucion();

  // setters
  void setId(const int i);
  void setTexto(const QString t);
  void setTextoTraducido(const QString t);
  void setTextoResumido(const QString t);
  void setCapitulo(const int c);
  void setEpigrafe(const QString e);
  void setProvincia(const int p);
  void setEntendido(const bool e);
  void setVolverMirar(const bool v);
  void setTraducido(const bool t);
  void setRazonada(const bool r);
  void setInteres(const int i);
  void setResolucionAnterior(const int r);
  void setVerbos(const QStringList v);
  void setExpresiones(const QStringList e);
  void setPages(const QString p);
  void setNotas(const QString n);

  // getters
  int getId() const { return id; }
  QString getTexto() const { return texto; }
  QString getTextoTraducido() const { return texto_traducido; }
  QString getTextoResumido() const { return texto_resumido; }
  int getCapitulo() const { return capitulo; }
  QString getEpigrafe() const { return epigrafe; }
  int getProvincia() const { return provincia; }
  bool getEntendido() const { return entendido; }
  bool getVolverMirar() const { return volveramirar; }
  bool getTraducido() const { return traducido; }
  bool getRazonada() const { return razonada; }
  int getInteres() const { return interes; }
  int getResolucionAnterior() const { return resolucion_anterior; }
  QStringList getVerbos() const { return verbos; }
  QStringList getExpresiones() const { return expresiones; }
  QString getPages() const { return pages; }
  QString getNotas() const { return notas; }

 private:
  int id;
  QString texto;
  QString texto_traducido;
  QString texto_resumido;
  int capitulo;
  QString epigrafe;
  int provincia;
  bool entendido;
  bool volveramirar;
  bool traducido;
  bool razonada;
  int interes;
  int resolucion_anterior;
  QStringList verbos;
  QStringList expresiones;
  QString pages;
  QString notas;
};

#endif  // RESOLUCION_H
