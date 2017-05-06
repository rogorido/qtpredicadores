#ifndef DLGSUFRAGIOSENTRADA_H
#define DLGSUFRAGIOSENTRADA_H

#include <QDialog>

namespace Ui {
class dlgSufragiosEntrada;
}

class dlgSufragiosEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSufragiosEntrada(QWidget *parent = 0);
    ~dlgSufragiosEntrada();

private:
    Ui::dlgSufragiosEntrada *ui;
};

#endif // DLGSUFRAGIOSENTRADA_H
