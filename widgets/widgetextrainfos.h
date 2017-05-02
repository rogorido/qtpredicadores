#ifndef WIDGETEXTRAINFOS_H
#define WIDGETEXTRAINFOS_H

#include <QWidget>

namespace Ui {
class WidgetExtraInfos;
}

class WidgetExtraInfos : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetExtraInfos(QWidget *parent = 0);
    ~WidgetExtraInfos();

private:
    Ui::WidgetExtraInfos *ui;
};

#endif // WIDGETEXTRAINFOS_H
