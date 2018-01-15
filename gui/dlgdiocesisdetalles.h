#ifndef DLGDIOCESISDETALLES_H
#define DLGDIOCESISDETALLES_H

#include <QWidget>

namespace Ui {
class dlgDiocesisDetalles;
}

class dlgDiocesisDetalles : public QWidget
{
    Q_OBJECT

public:
    explicit dlgDiocesisDetalles(int diocesis_id, QWidget *parent = 0);
    ~dlgDiocesisDetalles();

private:
    Ui::dlgDiocesisDetalles *ui;

    // la diócesis que estamos introduciendo
    int dioc_id;

};

#endif // DLGDIOCESISDETALLES_H
