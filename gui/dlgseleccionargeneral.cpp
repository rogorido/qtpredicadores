#include "dlgseleccionargeneral.h"
#include "ui_dlgseleccionargeneral.h"

dlgSeleccionarGeneral::dlgSeleccionarGeneral(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSeleccionarGeneral)
{
    ui->setupUi(this);
}

dlgSeleccionarGeneral::~dlgSeleccionarGeneral()
{
    delete ui;
}
