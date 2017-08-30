#ifndef DECLARACIONENTRADA_H
#define DECLARACIONENTRADA_H

#include <QDialog>

namespace Ui {
class DeclaracionEntrada;
}

class DeclaracionEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit DeclaracionEntrada(QWidget *parent = 0);
    ~DeclaracionEntrada();

private:
    Ui::DeclaracionEntrada *ui;
};

#endif // DECLARACIONENTRADA_H
