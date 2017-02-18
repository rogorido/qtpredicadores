#ifndef DLGCAPITULOS_H
#define DLGCAPITULOS_H

#include <QDialog>

namespace Ui {
class DlgCapitulos;
}

class DlgCapitulos : public QDialog
{
    Q_OBJECT

public:
    explicit DlgCapitulos(QWidget *parent = 0);
    ~DlgCapitulos();

private:
    Ui::DlgCapitulos *ui;
};

#endif // DLGCAPITULOS_H
