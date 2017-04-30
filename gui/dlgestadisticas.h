#ifndef DLGESTADISTICAS_H
#define DLGESTADISTICAS_H

#include <QDialog>

namespace Ui {
class dlgEstadisticas;
}

class dlgEstadisticas : public QDialog
{
    Q_OBJECT

public:
    explicit dlgEstadisticas(QWidget *parent = 0);
    ~dlgEstadisticas();

private:
    Ui::dlgEstadisticas *ui;
};

#endif // DLGESTADISTICAS_H
