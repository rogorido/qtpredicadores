#ifndef DLGNUEVAMISIONFILIPINAS_H
#define DLGNUEVAMISIONFILIPINAS_H

#include <QDialog>

namespace Ui {
class dlgNuevaMisionFilipinas;
}

class dlgNuevaMisionFilipinas : public QDialog
{
    Q_OBJECT

public:
    explicit dlgNuevaMisionFilipinas(QWidget *parent = 0);
    ~dlgNuevaMisionFilipinas();

private:
    Ui::dlgNuevaMisionFilipinas *ui;
};

#endif // DLGNUEVAMISIONFILIPINAS_H
