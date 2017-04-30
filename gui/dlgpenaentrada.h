#ifndef DLGPENAENTRADA_H
#define DLGPENAENTRADA_H

#include <QDialog>

namespace Ui {
class dlgPenaEntrada;
}

class dlgPenaEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgPenaEntrada(QWidget *parent = 0);
    ~dlgPenaEntrada();

private:
    Ui::dlgPenaEntrada *ui;
};

#endif // DLGPENAENTRADA_H
