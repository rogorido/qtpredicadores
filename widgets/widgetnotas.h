#ifndef WIDGETNOTAS_H
#define WIDGETNOTAS_H

#include <QWidget>

namespace Ui {
class WidgetNotas;
}

class WidgetNotas : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetNotas(QWidget *parent = 0);
    ~WidgetNotas();

private:
    Ui::WidgetNotas *ui;
};

#endif // WIDGETNOTAS_H
