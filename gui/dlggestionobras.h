#ifndef DLGGESTIONOBRAS_H
#define DLGGESTIONOBRAS_H

#include <QWidget>

namespace Ui {
class dlgGestionObras;
}

class dlgGestionObras : public QWidget
{
    Q_OBJECT

public:
    explicit dlgGestionObras(QWidget *parent = nullptr);
    ~dlgGestionObras();

private:
    Ui::dlgGestionObras *ui;
};

#endif // DLGGESTIONOBRAS_H
