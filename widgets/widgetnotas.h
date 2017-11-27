#ifndef WIDGETNOTAS_H
#define WIDGETNOTAS_H

#include <QWidget>

#include "objs/notas.h"

class QJsonObject;

namespace Ui {
class WidgetNotas;
}

class WidgetNotas : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetNotas(QWidget *parent = 0);
    ~WidgetNotas();

    void reiniciar();

    void importNota(const QJsonObject nota_json);

    bool haCambiado();
    Notas getNotas();

private:
    Ui::WidgetNotas *ui;

    Notas nota;
    bool cambiado;
};

#endif // WIDGETNOTAS_H
