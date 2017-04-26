#include "dlgciudades.h"
#include "ui_dlgciudades.h"

dlgCiudades::dlgCiudades(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgCiudades)
{
    ui->setupUi(this);
}

dlgCiudades::~dlgCiudades()
{
    delete ui;
}
