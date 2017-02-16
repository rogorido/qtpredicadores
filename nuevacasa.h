#ifndef NUEVACASA_H
#define NUEVACASA_H

#include <QDialog>

namespace Ui {
class NuevaCasa;
}

class NuevaCasa : public QDialog
{
    Q_OBJECT

public:
    explicit NuevaCasa(QWidget *parent = 0);
    ~NuevaCasa();

private:
    Ui::NuevaCasa *ui;
};

#endif // NUEVACASA_H
