#ifndef NUEVOCAPITULO_H
#define NUEVOCAPITULO_H

#include <QDialog>

namespace Ui {
class NuevoCapitulo;
}

class NuevoCapitulo : public QDialog
{
    Q_OBJECT

public:
    explicit NuevoCapitulo(QWidget *parent = 0);
    ~NuevoCapitulo();

private:
    Ui::NuevoCapitulo *ui;
};

#endif // NUEVOCAPITULO_H
