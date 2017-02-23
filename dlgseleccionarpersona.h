#ifndef DLGSELECCIONARPERSONA_H
#define DLGSELECCIONARPERSONA_H

#include <QDialog>

namespace Ui {
class dlgSeleccionarPersona;
}

class dlgSeleccionarPersona : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSeleccionarPersona(QWidget *parent = 0);
    ~dlgSeleccionarPersona();

private:
    Ui::dlgSeleccionarPersona *ui;
};

#endif // DLGSELECCIONARPERSONA_H
