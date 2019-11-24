#ifndef DLGENTRADAMISIONERO_H
#define DLGENTRADAMISIONERO_H

#include <QJsonObject>
#include <QWidget>

#include "src/objs/persona.h"
#include "src/objs/variados.h"

class MyQmdiArea;

namespace Ui {
class dlgEntradaMisionero;
}

class dlgEntradaMisionero : public QWidget {
  Q_OBJECT

 public:
  explicit dlgEntradaMisionero(int mision, QWidget *parent = 0);
  ~dlgEntradaMisionero();

 private slots:

  void anadirPersona();
  void anadirFuente();

  void recibirPersona(Persona persona);
  void recibirFuente(fuente datoobra);

  void cerrar();
  void aceptarMisionero();

 private:
  Ui::dlgEntradaMisionero *ui;
  MyQmdiArea *mdiarea;

  int mision_id;
  int persona_id = 0;
  bool fuente_recibida = false;

  /*
   * aquí metemos los datos que nos llegan de la source
   */
  QJsonObject *fuentedatos;

  void borrarCampos();
};

#endif  // DLGENTRADAMISIONERO_H
