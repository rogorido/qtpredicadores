#ifndef DLGAPROBACIONESENTRADA_H
#define DLGAPROBACIONESENTRADA_H

#include <QDialog>

namespace Ui {
class dlgAprobacionesEntrada;
}

class dlgAprobacionesEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgAprobacionesEntrada(QWidget *parent = 0);
    ~dlgAprobacionesEntrada();

private:
    Ui::dlgAprobacionesEntrada *ui;
};

#endif // DLGAPROBACIONESENTRADA_H
