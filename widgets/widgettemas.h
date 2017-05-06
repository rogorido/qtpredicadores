#ifndef WIDGETTEMAS_H
#define WIDGETTEMAS_H

#include <QWidget>

namespace Ui {
class WidgetTemas;
}

class WidgetTemas : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetTemas(QWidget *parent = 0);
    ~WidgetTemas();

private:
    Ui::WidgetTemas *ui;
};

#endif // WIDGETTEMAS_H
