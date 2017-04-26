#ifndef DLGCASAS_H
#define DLGCASAS_H

#include <QDialog>

class QSqlRelationalTableModel;

namespace Ui {
class dlgCasas;
}

class dlgCasas : public QDialog
{
    Q_OBJECT

public:
    explicit dlgCasas(QWidget *parent = 0);
    ~dlgCasas();

private:
    Ui::dlgCasas *ui;

    QSqlRelationalTableModel *casas_model;

    void cargarModelos();
};

#endif // DLGCASAS_H
