#ifndef NUEVARESOLUCION_H
#define NUEVARESOLUCION_H

#include <QDialog>

namespace Ui {
class NuevaResolucion;
}

class NuevaResolucion : public QDialog
{
    Q_OBJECT

public:
    explicit NuevaResolucion(QWidget *parent = 0);
    ~NuevaResolucion();

private:
    Ui::NuevaResolucion *ui;
};

#endif // NUEVARESOLUCION_H
