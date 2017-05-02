#ifndef WIDGETEXTRAINFOS_H
#define WIDGETEXTRAINFOS_H

#include <QWidget>

#include "objs/variados.h"

namespace Ui {
class WidgetExtraInfos;
}

class WidgetExtraInfos : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetExtraInfos(QWidget *parent = 0);
    ~WidgetExtraInfos();

    ExtraInfos getExtraInfos();
    void clear();

private slots:

    void anadirPar();
    void eliminarPar();

private:
    Ui::WidgetExtraInfos *ui;

    ExtraInfos extras;
};

#endif // WIDGETEXTRAINFOS_H
