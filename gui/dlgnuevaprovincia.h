#ifndef DLGNUEVAPROVINCIA_H
#define DLGNUEVAPROVINCIA_H

#include <QDialog>

namespace Ui {
class dlgNuevaProvincia;
}

class dlgNuevaProvincia : public QDialog
{
    Q_OBJECT

public:
    explicit dlgNuevaProvincia(QWidget *parent = 0);
    ~dlgNuevaProvincia();

private:
    Ui::dlgNuevaProvincia *ui;
};

#endif // DLGNUEVAPROVINCIA_H
