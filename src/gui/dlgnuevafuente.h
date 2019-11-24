#ifndef DLGNUEVAFUENTE_H
#define DLGNUEVAFUENTE_H

#include <QDialog>

namespace Ui {
class dlgNuevaFuente;
}

class dlgNuevaFuente : public QDialog {
  Q_OBJECT

 public:
  explicit dlgNuevaFuente(QWidget *parent = 0);
  ~dlgNuevaFuente();

 protected:
  void accept();

 private:
  Ui::dlgNuevaFuente *ui;
};

#endif  // DLGNUEVAFUENTE_H
