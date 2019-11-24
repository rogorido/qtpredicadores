#ifndef DLGMISIONES_H
#define DLGMISIONES_H

#include <QWidget>

class QSqlTableModel;
class dlgEntradaMisionero;
class MyQmdiArea;

namespace Ui {
class dlgMisiones;
}

class dlgMisiones : public QWidget {
  Q_OBJECT

 public:
  explicit dlgMisiones(QWidget *parent = 0);
  ~dlgMisiones();

 private slots:

  void anadirMisionero();

 private:
  Ui::dlgMisiones *ui;
  MyQmdiArea *mdiArea;
  dlgEntradaMisionero *dlgMisionero;

  QSqlTableModel *m_misiones;

  // id de la misión escogida
  int mision_escogida;

  void cargarModelo();
};

#endif  // DLGMISIONES_H
