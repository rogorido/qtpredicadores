#ifndef DLGPENA_H
#define DLGPENA_H

#include <QDialog>

namespace Ui {
class dlgPena;
}

class dlgPena : public QDialog
{
    Q_OBJECT

public:
    explicit dlgPena(QWidget *parent = 0);
    ~dlgPena();

private:
    Ui::dlgPena *ui;
};

#endif // DLGPENA_H
