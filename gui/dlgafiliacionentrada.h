#ifndef DLGAFILIACIONENTRADA_H
#define DLGAFILIACIONENTRADA_H

#include <QDialog>

namespace Ui {
class dlgAfiliacionEntrada;
}

class dlgAfiliacionEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgAfiliacionEntrada(QWidget *parent = 0);
    ~dlgAfiliacionEntrada();

private:
    Ui::dlgAfiliacionEntrada *ui;
};

#endif // DLGAFILIACIONENTRADA_H
