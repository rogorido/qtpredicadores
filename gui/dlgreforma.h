#ifndef DLGREFORMA_H
#define DLGREFORMA_H

#include <QDialog>

#include "objs/variados.h"
#include "objs/lugar.h"

namespace Ui {
class dlgReforma;
}

class dlgReforma : public QDialog
{
    Q_OBJECT

public:
    explicit dlgReforma(QWidget *parent = 0);
    ~dlgReforma();

private slots:

    void anadirLugar();
    void quitarLugar();
    void aceptar();

    void recibirLugar(Lugar lugar);

private:
    Ui::dlgReforma *ui;

    elementopareado lugar_struct;
};

#endif // DLGREFORMA_H
