#ifndef DLGFUENTEENTRADA_H
#define DLGFUENTEENTRADA_H

#include <QDialog>

namespace Ui {
class dlgFuenteEntrada;
}

class dlgFuenteEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgFuenteEntrada(QWidget *parent = 0);
    ~dlgFuenteEntrada();

private:
    Ui::dlgFuenteEntrada *ui;
};

#endif // DLGFUENTEENTRADA_H
