#ifndef DLGNUEVADIOCESIS_H
#define DLGNUEVADIOCESIS_H

#include <QDialog>

namespace Ui {
class dlgNuevaDiocesis;
}

class dlgNuevaDiocesis : public QDialog
{
    Q_OBJECT

public:
    explicit dlgNuevaDiocesis(QWidget *parent = 0);
    ~dlgNuevaDiocesis();

private:
    Ui::dlgNuevaDiocesis *ui;
};

#endif // DLGNUEVADIOCESIS_H
