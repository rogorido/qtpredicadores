#ifndef DLGNUEVOLUGAR_H
#define DLGNUEVOLUGAR_H

#include <QWidget>

class QJsonModel;
class LugaresModel;
class QSqlQueryModel;
class QCompleter;
class dlgDetalles;

class MyQmdiArea;

namespace Ui {
class dlgNuevoLugar;
}

class dlgNuevoLugar : public QWidget {
  Q_OBJECT

 public:
  explicit dlgNuevoLugar(QWidget *parent = 0);
  ~dlgNuevoLugar();

 private slots:

  void anadirDetalles();
  void aceptar();
  void cerrar();

 private:
  Ui::dlgNuevoLugar *ui;
  MyQmdiArea *mdiarea;

  dlgDetalles *dlgdetalles;

  QJsonModel *otrosnombres;
  LugaresModel *m_lugares;

  QSqlQueryModel *m_paises;
  // QSqlQueryModel *m_tipos;
  QCompleter *m_paises_completer;
  QCompleter *m_tipos_completer;

  void cargarModelos();
  void borrarCampos();
};

#endif  // DLGNUEVOLUGAR_H
