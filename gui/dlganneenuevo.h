#ifndef DLGANNEENUEVO_H
#define DLGANNEENUEVO_H

#include <QWidget>

namespace Ui {
class dlgAnneeNuevo;
}

class dlgAnneeNuevo : public QWidget
{
    Q_OBJECT

public:
    explicit dlgAnneeNuevo(QWidget *parent = 0);
    ~dlgAnneeNuevo();

private:
    Ui::dlgAnneeNuevo *ui;
};

#endif // DLGANNEENUEVO_H
