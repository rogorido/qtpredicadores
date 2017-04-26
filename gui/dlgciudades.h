#ifndef DLGCIUDADES_H
#define DLGCIUDADES_H

#include <QDialog>

namespace Ui {
class dlgCiudades;
}

class dlgCiudades : public QDialog
{
    Q_OBJECT

public:
    explicit dlgCiudades(QWidget *parent = 0);
    ~dlgCiudades();

private:
    Ui::dlgCiudades *ui;
};

#endif // DLGCIUDADES_H
