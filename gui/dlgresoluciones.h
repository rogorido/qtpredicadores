#ifndef DLGRESOLUCIONES_H
#define DLGRESOLUCIONES_H

#include <QDialog>

namespace Ui {
class DlgResoluciones;
}

class DlgResoluciones : public QDialog
{
    Q_OBJECT

public:
    explicit DlgResoluciones(QWidget *parent = 0);
    ~DlgResoluciones();

private:
    Ui::DlgResoluciones *ui;
};

#endif // DLGRESOLUCIONES_H
