#ifndef DLGDETALLES_H
#define DLGDETALLES_H

#include <QDialog>

#include "objs/persona.h"

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
    void recibirPersona(Persona persona);
    void on_btPersona_clicked();

private:
    Ui::dlgDetalles *ui;

    JsonGestor *jsondetalles;
};

#endif // DLGDETALLES_H
