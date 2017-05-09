#ifndef WIDGETNOTAS_H
#define WIDGETNOTAS_H

#include <QWidget>

#include "objs/notas.h"

namespace Ui {
class WidgetNotas;
}

class WidgetNotas : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetNotas(QWidget *parent = 0);
    ~WidgetNotas();

    bool haCambiado();
    Notas getNotas();

private:
    Ui::WidgetNotas *ui;

    Notas nota;
    bool cambiado;
};

#endif // WIDGETNOTAS_H
