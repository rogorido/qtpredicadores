#ifndef DLGMASIVO_H
#define DLGMASIVO_H

#include <QDialog>

namespace Ui {
class dlgMasivo;
}

class dlgMasivo : public QDialog
{
    Q_OBJECT

public:
    explicit dlgMasivo(QWidget *parent = 0);
    ~dlgMasivo();

private:
    Ui::dlgMasivo *ui;
};

#endif // DLGMASIVO_H
