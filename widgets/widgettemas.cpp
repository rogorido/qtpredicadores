#include "widgettemas.h"
#include "ui_widgettemas.h"

WidgetTemas::WidgetTemas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetTemas)
{
    ui->setupUi(this);
}

WidgetTemas::~WidgetTemas()
{
    delete ui;
}
