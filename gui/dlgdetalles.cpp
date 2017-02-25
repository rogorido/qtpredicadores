#include "dlgdetalles.h"
#include "ui_dlgdetalles.h"

dlgDetalles::dlgDetalles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgDetalles)
{
    ui->setupUi(this);
}

dlgDetalles::~dlgDetalles()
{
    delete ui;
}
