#ifndef DLGGESTIONOBRAS_H
#define DLGGESTIONOBRAS_H

#include <QWidget>

#include "src/objs/persona.h"
#include "src/objs/tema.h"
#include "src/objs/variados.h"

class QMenu;
class QAction;
class QSqlQueryModel;
class QModelIndex;

class dlgNuevaObra;

class MyQmdiArea;

class ObrasModel;
class SqlFiltroGestor;
class QJsonModel;

namespace Ui {
class dlgGestionObras;
}

class dlgGestionObras : public QWidget {
  Q_OBJECT

 public:
  explicit dlgGestionObras(QWidget *parent = 0);
  ~dlgGestionObras();

  // esto es público porque lo accedemos desde el mainwindow...
  void contarTotal();

 private slots:

  // GUI
  void on_rbManuscritos_clicked();
  void on_rbImpresos_clicked();
  void on_rbTodos_clicked();
  void on_ckSinMateria_stateChanged(int arg1);
  void on_pbAnadirTema_clicked();
  void on_pbQuitarTema_clicked();
  void on_pbQuitarTemasTodos_clicked();
  void on_ckConReedicion_stateChanged(int arg1);
  void on_pbAnadirAutor_clicked();
  void on_pbQuitarAutor_clicked();
  void on_pbQuitarAutoresTodos_clicked();
  void on_pbResetearFiltros_clicked();
  void on_btModificarObra_clicked();

  void menuContextual(const QPoint &point);

  void actualizarSqlGeneral(const QString s);
  void actualizarSqlEstadisticas(const QString s);

  void modificarObra();
  void verPersona();
  void modificarPersona();

  /*
   * Actualizar el modelo tras recibir la señal de dlgNuevaObra
   * de que se ha actualizado una obra
   */
  void actualizarModeloTrasObraActualizada();

  // para emitir la señal de que se ha seleccionado una obra
  void seleccionarObra(const QModelIndex &idx);

  void recibirTema(const Tema tema);
  void recibirAutor(const Persona autor);

 signals:

  void infoBarra(int filtrados);
  void infoObraSeleccionada(QString info);
  void infoObraSeleccionadaBorrar();  // al salir borramos la statusbar

 private:
  Ui::dlgGestionObras *ui;
  MyQmdiArea *mdiarea;

  /*
   * TODO: esto realmente debería ser uno solo. Es decir, hay que convertir
   * ObrasModel en un QsqlQuerymodel que devuelva un data(), etc.
   * como tengo ya con PersonasModel y CasaModel
   */
  ObrasModel *obras_model;
  QSqlQueryModel *works_model;
  /*
   * Aquí cogemos una abfrage que nos muestra estadísticas del número de
   * reediciones que vamos a poner en el segundo tab
   */
  QSqlQueryModel *works_statistics_model;

  /*
   * tenemos un gestor para cada modelo
   */
  SqlFiltroGestor *sql_gestor_general;
  SqlFiltroGestor *sql_gestor_estadisticas;

  QMenu *menuContexto;
  QAction *a_verPersona;
  QAction *a_cambiarPersona;
  QAction *a_cambiarObra;

  /*
   * guardamos los SQLs que están activos
   */
  QString sqlactivo_general;
  QString sqlactivo_estadisticas;

  // work_id
  int work_id;

  // lo usamos para la barra
  int total_filtrado;

  QJsonModel *json_detalles;

  // esto para modificar obras,... por qué carajo lo hago como pointer?
  dlgNuevaObra *dlgObraAModificar;

  // para filtrar por materias
  QList<elementopareado> materias_escogidas;
  // para filtrar por autores
  QList<elementopareado> autores_escogidos;

  void cargarMenus();
  void cargarModelos();

  void generarSQLMaterias();
  void generarSQLAutores();

  void mostrarDetalles(const int obra_id);
  void mostrarMaterias(const int obra_id);
};

#endif  // DLGGESTIONOBRAS_H
