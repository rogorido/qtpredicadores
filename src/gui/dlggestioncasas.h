#ifndef DLGGESTIONCASAS_H
#define DLGESTIONCASAS_H

#include <QWidget>

#include "src/objs/provincia.h"
#include "src/objs/variados.h"

class CasasModel;
class ProxyNombres;
class SqlFiltroGestor;
class dlgNuevaCasa;

class MyQmdiArea;

class QSqlQueryModel;

namespace Ui {
class dlgGestionCasas;
}

class dlgGestionCasas : public QWidget {
  Q_OBJECT

 public:
  explicit dlgGestionCasas(QWidget *parent = 0);
  ~dlgGestionCasas();

 private slots:

  // GUI
  void on_btModificar_clicked();
  void on_rbFemeninas_toggled(bool checked);
  void on_rbMasculinas_toggled(bool checked);
  void on_rbTodas_toggled(bool checked);
  void on_btAnadirProvincia_clicked();
  void on_btResetearFiltros_clicked();
  void on_btQuitarTodasProvincias_clicked();
  void on_btAnadirTipo_clicked();
  void on_btQuitarTipo_clicked();
  void on_btQuitarTiposTodos_clicked();
  void on_btQuitarProvincia_clicked();

  void actualizarFiltro(const QString filtro);

  // para emitir la señal de que se ha seleccionado una persona
  void seleccionarCasa(const QModelIndex &idx);
  void actualizarModeloTrasCasaIntroducida();

  void recibirProvincia(const Provincia provincia);

  void actualizarSql(QString s);
  void cerrar();

 signals:

  void infoBarra(int filtrado);

 private:
  Ui::dlgGestionCasas *ui;
  MyQmdiArea *mdiarea;

  CasasModel *m_casas;
  ProxyNombres *proxy_casas;

  SqlFiltroGestor *sql_gestor;

  QString sqlactivo;

  // esto para modificar obras,... por qué carajo lo hago como pointer?
  // realmente este form lo he ido copiando de otros anteriores...
  dlgNuevaCasa *dlgCasaAModificar;

  // para filtrar por provincias
  QList<elementopareado> provincias_escogidas;
  QSet<QString> tipos_escogidos;

  QSqlQueryModel *m_tiposcasas;

  void cargarModelos();

  /*
   * Al añadir/quitar provincias, para que actualice el filtro
   */
  void generarSQLProvincias();
  /*
   * Al añadir/quitar provincias, para que actualice el filtro
   */
  void generarSQLTipos();
};

#endif  // DLGESTIONCASAS_H
