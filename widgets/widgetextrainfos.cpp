#include "widgetextrainfos.h"
#include "ui_widgetextrainfos.h"

WidgetExtraInfos::WidgetExtraInfos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetExtraInfos)
{
    ui->setupUi(this);
}

WidgetExtraInfos::~WidgetExtraInfos()
{
    delete ui;
}
