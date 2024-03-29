#ifndef DLGINFRACCIONENTRADA_H
#define DLGINFRACCIONENTRADA_H

#include <QWidget>

#include "src/objs/infraccion.h"
#include "src/objs/variados.h"

class QSqlQueryModel;
class QCompleter;

namespace Ui {
class dlgInfraccionEntrada;
}

class dlgInfraccionEntrada : public QWidget {
  Q_OBJECT

 public:
  explicit dlgInfraccionEntrada(QWidget *parent = 0);
  ~dlgInfraccionEntrada();

 private slots:

  void aceptar();

  void anadirInfractor();
  void quitarInfractor();

  void cerrar();

 signals:

  void aceptarInfraccion(Infraccion infraccion);

 protected:
  bool eventFilter(QObject *obj, QEvent *e);

 private:
  Ui::dlgInfraccionEntrada *ui;

  Infraccion infraccion;

  QStringList lista_infractores;

  QSqlQueryModel *tipos_model;
  QCompleter *tipos_completer;
  QSqlQueryModel *infractores_model;
  QCompleter *infractores_completer;
  QSqlQueryModel *infraccion_model;
  QCompleter *infraccion_completer;

  void cargarModelos();
};

#endif  // DLGINFRACCIONENTRADA_H
