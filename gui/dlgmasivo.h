#ifndef DLGMASIVO_H
#define DLGMASIVO_H

#include <QDialog>

class JsonGestor;

namespace Ui {
class dlgMasivo;
}

class dlgMasivo : public QDialog
{
    Q_OBJECT

public:
    explicit dlgMasivo(JsonGestor *json, QWidget *parent = 0);
    ~dlgMasivo();

private:
    Ui::dlgMasivo *ui;
    JsonGestor *jsondetalles;
};

#endif // DLGMASIVO_H
