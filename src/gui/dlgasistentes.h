#ifndef DLGASISTENTES_H
#define DLGASISTENTES_H

#include <QDialog>

#include "src/objs/casa.h"
#include "src/objs/variados.h"

class QSqlTableModel;
class MyQmdiArea;

namespace Ui {
class dlgAsistentes;
}

class dlgAsistentes : public QDialog {
  Q_OBJECT

 public:
  /*
   * el int chapter es cuando lo abrimos desde el formulario
   * de gestión de chapters.
   */
  explicit dlgAsistentes(int chapter, QWidget *parent = 0);
  ~dlgAsistentes();

 private slots:

  /*
   * NOTE: esto es una chapuza, pues repito el código, pero ahora
   * no quiero estar adaptándolo a que sea aceptar con provincias o con
   * casas y por eso hago dos métodos.
   */
  void aceptar();
  void aceptarCasas();

  void anadirProvincia();
  void quitarProvincia();
  void anadirCasa();
  void quitarCasa();

  void recibirCasa(Casa casa);

 private:
  Ui::dlgAsistentes *ui;
  MyQmdiArea *mdiarea;

  QList<elementopareado> provinciasescogidas;
  QList<elementopareado> casasescogidas;

  /*
   * no uso el que ya tengo pq aquí cojo solo las columnas
   * que me interesan y así no tengo que estar ocultando
   * columnas en las views, que me aburre...
   * pero realmente es sensato?
   */
  QSqlTableModel *provincias;

  void desmarcarTodasProvincias();
  void cargarModelos();

  int chapterescogido;
};

#endif  // DLGASISTENTES_H
