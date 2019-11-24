#ifndef PROVINCIA_H
#define PROVINCIA_H

#include <QString>

class Provincia {
 public:
  Provincia();

  void setId(const int i);
  void setNombre(const QString n);
  void setOtrosNombres(const QString o);
  void setErigida(const QString e);
  void setNotas(const QString n);

  // getters
  int getId() const { return id; }
  QString getNombre() const { return nombre; }
  QString getOtrosNombres() const { return otrosnombres; }
  QString getErigida() const { return erigida; }
  QString getNotas() const { return notas; }
  bool estaLleno() const { return lleno; }

 private:
  int id;
  QString nombre;
  QString otrosnombres;
  QString erigida;
  QString notas;
  bool lleno = false;
};

#endif  // PROVINCIA_H
