#ifndef DLGREFORMA_H
#define DLGREFORMA_H

#include <QDialog>

namespace Ui {
class dlgReforma;
}

class dlgReforma : public QDialog
{
    Q_OBJECT

public:
    explicit dlgReforma(QWidget *parent = 0);
    ~dlgReforma();

private:
    Ui::dlgReforma *ui;
};

#endif // DLGREFORMA_H
