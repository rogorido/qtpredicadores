#ifndef DLGVIAJEENTRADA_H
#define DLGVIAJEENTRADA_H

#include <QWidget>

namespace Ui {
class dlgViajeEntrada;
}

class dlgViajeEntrada : public QWidget
{
    Q_OBJECT

public:
    explicit dlgViajeEntrada(QWidget *parent = 0);
    ~dlgViajeEntrada();

private:
    Ui::dlgViajeEntrada *ui;
};

#endif // DLGVIAJEENTRADA_H
