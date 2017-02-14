#ifndef NUEVOCAPITULO_H
#define NUEVOCAPITULO_H

#include <QWidget>

namespace Ui {
class NuevoCapitulo;
}

class NuevoCapitulo : public QWidget
{
    Q_OBJECT

public:
    explicit NuevoCapitulo(QWidget *parent = 0);
    ~NuevoCapitulo();

private:
    Ui::NuevoCapitulo *ui;
};

#endif // NUEVOCAPITULO_H
