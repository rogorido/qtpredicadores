#ifndef DLGLICENCIAENTRADA_H
#define DLGLICENCIAENTRADA_H

#include <QDialog>

namespace Ui {
class dlgLicenciaEntrada;
}

class dlgLicenciaEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgLicenciaEntrada(QWidget *parent = 0);
    ~dlgLicenciaEntrada();

private:
    Ui::dlgLicenciaEntrada *ui;
};

#endif // DLGLICENCIAENTRADA_H
