#ifndef DLGNUEVADIOCESIS_H
#define DLGNUEVADIOCESIS_H

#include <QWidget>

#include "src/objs/diocesis.h"
#include "src/objs/lugar.h"

class DiocesisModel;
class LugaresModel;
class MyQmdiArea;
class QStringList;
class QCompleter;

namespace Ui {
class dlgNuevaDiocesis;
}

class dlgNuevaDiocesis : public QWidget {
  Q_OBJECT

 public:
  explicit dlgNuevaDiocesis(QWidget *parent = 0);
  explicit dlgNuevaDiocesis(int diocesis, QWidget *parent = 0);
  ~dlgNuevaDiocesis();

 private slots:

  void aceptarDiocesis();
  void borrarCampos();

  void anadirLugar();
  void anadirArchiDiocesis();

  void recibirLugar(Lugar lugarrecibido);
  void recibirArchiDiocesis(Diocesis diocesis);

  void cerrar();

 private:
  Ui::dlgNuevaDiocesis *ui;
  MyQmdiArea *mdiarea;

  DiocesisModel *m_diocesis;
  LugaresModel *m_lugares;

  /*
   * aquí metemos esos valores que vendrían del
   * formulario seleccionar.
   */

  int sufraganea = 0;
  int lugar = 0;

  /*
   * para meter lo de los motivos de desaparición
   */
  QStringList *lista_motivos;
  QCompleter *motivos_completer;

  /*
   * variables para cuando abrimos el form
   * para modificar una existente
   */
  bool modificando = false;
  int diocesis_modificando;

  /*
   * ponemos aquí todo lo de las signals, etc.
   * que es común a los dos contructors que tenemos
   */
  void cargarUI();

  void cargarDiocesis();
};

#endif  // DLGNUEVADIOCESIS_H
