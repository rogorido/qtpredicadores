#include "dlgnuevaobra.h"
#include "ui_dlgnuevaobra.h"

dlgNuevaObra::dlgNuevaObra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaObra)
{
    ui->setupUi(this);
}

dlgNuevaObra::~dlgNuevaObra()
{
    delete ui;
}
