#ifndef DLGGESTIONCASAS_H
#define DLGESTIONCASAS_H

#include <QWidget>

class CasasModel;

namespace Ui {
class dlgGestionCasas;
}

class dlgGestionCasas : public QWidget
{
    Q_OBJECT

public:
    explicit dlgGestionCasas(QWidget *parent = 0);
    ~dlgGestionCasas();

private slots:

    void cerrar();

private:
    Ui::dlgGestionCasas *ui;

    CasasModel *casas_model;

    void cargarModelos();
};

#endif // DLGESTIONCASAS_H
