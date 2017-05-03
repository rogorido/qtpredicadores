#ifndef DLGORDENANZAENTRADA_H
#define DLGORDENANZAENTRADA_H

#include <QDialog>

namespace Ui {
class dlgOrdenanzaEntrada;
}

class dlgOrdenanzaEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgOrdenanzaEntrada(QWidget *parent = 0);
    ~dlgOrdenanzaEntrada();

private:
    Ui::dlgOrdenanzaEntrada *ui;
};

#endif // DLGORDENANZAENTRADA_H
