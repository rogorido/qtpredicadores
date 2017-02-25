#ifndef DLGDETALLES_H
#define DLGDETALLES_H

#include <QDialog>

class JsonGestor;

namespace Ui {
class dlgDetalles;
}

class dlgDetalles : public QDialog
{
    Q_OBJECT

public:
    explicit dlgDetalles(JsonGestor *json, QWidget *parent = 0);
    ~dlgDetalles();

private slots:


private:
    Ui::dlgDetalles *ui;

    JsonGestor *jsondetalles;
};

#endif // DLGDETALLES_H
