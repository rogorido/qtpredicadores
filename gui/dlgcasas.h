#ifndef DLGCASAS_H
#define DLGCASAS_H

#include <QDialog>

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
};

#endif // DLGCASAS_H
