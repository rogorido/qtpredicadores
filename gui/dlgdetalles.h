#ifndef DLGDETALLES_H
#define DLGDETALLES_H

#include <QDialog>

namespace Ui {
class dlgDetalles;
}

class dlgDetalles : public QDialog
{
    Q_OBJECT

public:
    explicit dlgDetalles(QWidget *parent = 0);
    ~dlgDetalles();

private:
    Ui::dlgDetalles *ui;
};

#endif // DLGDETALLES_H
