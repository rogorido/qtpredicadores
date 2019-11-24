#ifndef WIDGETTEMAS_H
#define WIDGETTEMAS_H

#include <QWidget>

class QSqlTableModel;
class QSortFilterProxyModel;

namespace Ui {
class WidgetTemas;
}

class WidgetTemas : public QWidget {
  Q_OBJECT

 public:
  explicit WidgetTemas(QWidget *parent = 0);
  ~WidgetTemas();

 signals:

  /*
   * devolvemos una Qlist<int> con los ids de los
   * temas seleccionados para que luego el formulario que
   * la recibe se las apañe... ¿O hacer aquí algo más elaborado?
   */
  void temasSeleccionadosCambio(QList<int> temas_seleccionados);

 private slots:
  void on_btAnadir_clicked();

  void on_btQuitar_clicked();

  void on_btQuitarTodos_clicked();

 private:
  Ui::WidgetTemas *ui;

  QSqlTableModel *m_temas;
  QSortFilterProxyModel *temas_noseleccionados_proxy;
  QSortFilterProxyModel *temas_seleccionados_proxy;

  void cargarModelos();
  void crearSqlFiltro();
};

#endif  // WIDGETTEMAS_H
