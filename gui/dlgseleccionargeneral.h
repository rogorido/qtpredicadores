#ifndef DLGSELECCIONARGENERAL_H
#define DLGSELECCIONARGENERAL_H

#include <QDialog>

namespace Ui {
class dlgSeleccionarGeneral;
}

class dlgSeleccionarGeneral : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSeleccionarGeneral(QWidget *parent = 0);
    ~dlgSeleccionarGeneral();

private:
    Ui::dlgSeleccionarGeneral *ui;
};

#endif // DLGSELECCIONARGENERAL_H
