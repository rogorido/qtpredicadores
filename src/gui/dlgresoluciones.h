#ifndef DLGRESOLUCIONES_H
#define DLGRESOLUCIONES_H

#include <QWidget>

#include "src/objs/tema.h"

class QSqlQueryModel;
class QSqlTableModel;
class QSortFilterProxyModel;
class QSqlRelationalTableModel;
class QDataWidgetMapper;
class QModelIndex;
class QJsonModel;

class dlgSeleccionarGeneral;
class dlgNuevaResolucion;
class SqlFiltroGestor;

class MyQmdiArea;

namespace Ui {
class dlgResoluciones;
}

/*
 * Realmente estoy idiota: he duplicado un poco el código para actualizar.
 * De hecho se puede hacer también desde aquí aunque creo que falta lo de json!
 */

class dlgResoluciones : public QWidget {
  Q_OBJECT

 public:
  explicit dlgResoluciones(QWidget *parent = 0);
  ~dlgResoluciones();

 private slots:

  void seleccionarResolucion(const QModelIndex &idx);
  void recibirNuevoTema(Tema t);
  // cuando añadimos detalles los recibimos en este slot
  void recibirNuevoJsonDetalles();
  void cargarDetalles(int id);
  void aplicarFiltro();
  void actualizarSql(QString s);
  // esto recibe del widget temas la lista de temas cambiados
  void temasSeleccionadosCambiados(QList<int> lista_temas);

  void on_btAnadirTema_clicked();
  void on_btQuitarTema_clicked();
  void on_btAnadirDetalles_clicked();
  void on_btBorrarDetalles_clicked();
  void on_btSeleccionarEpigrafe_clicked();
  void on_btDeSeleccionarEpigrafe_clicked();
  void on_btDeseleccionarTodosEpigrafes_clicked();
  void on_btActualizarResolucion_clicked();
  void on_btActualizarID_clicked();

 private:
  Ui::dlgResoluciones *ui;

  MyQmdiArea *mdiarea;

  dlgSeleccionarGeneral *dlgseleccionar;
  dlgNuevaResolucion *dlgresolucion;
  SqlFiltroGestor *sql_gestor;

  /*
   * no pongo m_resoluciones pq "se confundiría
   * con el que suelo usar que carga toda la tabla,
   * y aquí solo cargamos una parte y además con datos de otras
   */
  QSqlQueryModel *resoluciones_model;
  QDataWidgetMapper *mapper_data;
  QSqlRelationalTableModel *temas_model;
  QJsonModel *json_model;

  /*
   * esto lo usamos para la tabla temporal de epígrafes
   * de las resoluciones
   */
  QSqlTableModel *m_epigrafes;
  QSortFilterProxyModel *epigrafes_noseleccionados_proxy;
  QSortFilterProxyModel *epigrafes_seleccionados_proxy;

  /*
   * este lo usamos en el caso de que queramos
   * añadir nuevos Jsons a la resolución
   */
  QJsonModel *json_anadir_model;

  void cargarModelos();
  void cargarTablasTemporales();  // para lo de los epígrafes
  void cargarMapper();
  void cargarInfos();

  /*
   * aquí guardamos la id de la resolución que está escogida.
   */
  int resolucion_id;

  /*
   * aquí se guarda una lista de las ids de la tabla
   * resolutions_details, que se corresponde al campo
   * detail_id  y permite manipular las entradas de esta tabla
   */
  QList<int> ids_resolutions_details;

  /*
   * guardamos el SQL que está activo
   */
  QString sqlactivo;

  /*
   * Métodos para la creación de filtros que luego se pasan
   * a SqlFiltroGestor
   */
  void crearFiltroEpigrafes();
};

#endif  // DLGRESOLUCIONES_H
