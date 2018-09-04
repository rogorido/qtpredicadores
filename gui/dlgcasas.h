#ifndef DLGCASAS_H
#define DLGCASAS_H

#include <QWidget>

class CasasOwnModel;

namespace Ui {
class dlgCasas;
}

class dlgCasas : public QWidget
{
    Q_OBJECT

public:
    explicit dlgCasas(QWidget *parent = 0);
    ~dlgCasas();

private slots:

    void cerrar();

private:
    Ui::dlgCasas *ui;

    CasasOwnModel *casas_model;

    void cargarModelos();
};

#endif // DLGCASAS_H
