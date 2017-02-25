#include "dlgnuevaprovincia.h"
#include "ui_dlgnuevaprovincia.h"

dlgNuevaProvincia::dlgNuevaProvincia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaProvincia)
{
    ui->setupUi(this);
}

dlgNuevaProvincia::~dlgNuevaProvincia()
{
    delete ui;
}
