#ifndef DLGAFILIACIONENTRADA_H
#define DLGAFILIACIONENTRADA_H

#include <QDialog>

#include "src/models/afiliacionestablemodel.h"
#include "src/objs/afiliacion.h"
#include "src/objs/casa.h"
#include "src/objs/persona.h"
#include "src/objs/provincia.h"
#include "src/objs/variados.h"

class MyQmdiArea;

namespace Ui {
class dlgAfiliacionEntrada;
}

class dlgAfiliacionEntrada : public QDialog {
  Q_OBJECT

 public:
  explicit dlgAfiliacionEntrada(QWidget *parent = 0);
  ~dlgAfiliacionEntrada();

 signals:

  void aceptarDatos(QList<Afiliacion *> listaafiliciones);

 private slots:
  void anadirAfiliacion();
  void quitarAfiliacion();
  void aceptarAfiliaciones();
  void anadirPersona();
  void anadirCasaOrigen();
  void anadirCasaDestino();
  void anadirProvinciaOrigen();
  void anadirProvinciaDestino();

  void actualizarPersona(Persona persona);
  void actualizarCasaOrigen(Casa casa);
  void actualizarCasaDestino(Casa casa);
  void actualizarProvinciaOrigen(Provincia provincia);
  void actualizarProvinciaDestino(Provincia provincia);

  void cerrar();

 private:
  Ui::dlgAfiliacionEntrada *ui;
  MyQmdiArea *mdiarea;

  AfiliacionesTableModel *afiliaciones_model;

  /*
   * lo hago pointer pq luego necesito borrarla
   * para crear una nueva... pero esto sinceramente no sé
   * si está muy bien así. Al hacerlo pointer esto tb
   * me cambia internamente lo de AprobacionesTableModel
   */
  Afiliacion *afiliacion_activa;
};

#endif  // DLGAFILIACIONENTRADA_H
