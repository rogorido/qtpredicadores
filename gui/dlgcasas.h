#ifndef DLGCASAS_H
#define DLGCASAS_H

#include <QWidget>

class QSqlRelationalTableModel;

namespace Ui {
class dlgCasas;
}

class dlgCasas : public QWidget
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
