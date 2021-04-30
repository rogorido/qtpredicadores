#ifndef DLGNUEVARESOLUCION_H
#define DLGNUEVARESOLUCION_H

#include <QWidget>

#include "src/objs/capitulo.h"
#include "src/objs/provincia.h"
#include "src/objs/variados.h"

class TemasModel;
class ResolucionesModel;
class QJsonModel;
class dlgDetalles;
class dlgTemas;

class QSqlQueryModel;
class QCompleter;
class QStringListModel;

class MyQmdiArea;

namespace Ui {
class dlgNuevaResolucion;
}

class dlgNuevaResolucion : public QWidget {
  Q_OBJECT

 public:
  explicit dlgNuevaResolucion(int capitulo, QWidget *parent = 0);
  explicit dlgNuevaResolucion(int resolucionid, int capitulo,
                              QWidget *parent = 0);
  ~dlgNuevaResolucion();

 signals:

  void abrirDetalles(dlgDetalles *dlg);

 private:
  Ui::dlgNuevaResolucion *ui;

  MyQmdiArea *mdiarea;

  QJsonModel *jsongestor;
  dlgDetalles *dlgdetalles;
  dlgTemas *dlgtemas;

  ResolucionesModel *m_resoluciones;

  /*
   * esto no se define como pointer, pq luego no sé cómo
   * inicializarlo y es obligatorio antes de poder usarlo.
   * Lo que hago luego es pasarle una referencia a dlgtemas
   */
  QList<elementopareado> temas_lista;

  /*
   * si escogemos provincia lo metemos aquí
   * lo hacemos un pointer pq así luego se puede asignar
   * el valor NULL
   * Olvídalo!
   */
  int provincia_id = 0;
  int capitulo_id;
  QSqlQueryModel *m_epigrafe;
  QSqlQueryModel *m_verbos_usados;
  QSqlQueryModel *m_expresiones_usados;
  QCompleter *m_epigrafe_completer;
  QCompleter *m_verbos_completer;
  QCompleter *m_expresiones_completer;

  // para lo de los verbos y las expresiones
  QStringListModel *m_verbos;
  QStringListModel *m_expresiones;

  void cargarModelos();
  void cargarUI();
  void rellenarCombos();
  void introducirJson(const int id);
  void introducirTemas(const int id);
  void borrarCampos();

  /*
   * esto se usa cuando abrimos el formulario
   * desde el formulario de capítulo
   */
  int capitulo_origen;
  bool origen;

  // para actualizar resolucion
  int resolucionid;
  bool actualizando = false;

 private slots:

  void on_btDetalles_clicked();
  void on_btTemas_clicked();
  void on_btAnadirVerbo_clicked();
  void on_btQuitarVerbo_clicked();
  void on_btAnadirExpresion_clicked();
  void on_btQuitarExpresion_clicked();

  void aceptarResolucion();  // btOK

  void anadirProvincia();
  void quitarProvincia();

  void anadirCapitulo();
  void quitarCapitulo();

  // en teoría casi un qlist de ints sería suficiente...
  void recibirProvincia(Provincia provincia);
  void recibirCapitulo(Capitulo capitulo);

  void cerrar();
};

#endif  // DLGNUEVARESOLUCION_H
