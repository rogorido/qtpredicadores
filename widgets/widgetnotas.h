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

    Notas getNotas();

signals:
    /*
     * esta señal se envía cuando el texto de
     * notas ha cambiado pq así podemos poner en el otro
     * formulario un SLOT que active una variable
     * que advierta: hay que coger la nota!
     */

    void textoIntroducido();

private slots:
    void on_txtNota_textChanged();

private:
    Ui::WidgetNotas *ui;

    Notas nota;
};

#endif // WIDGETNOTAS_H
