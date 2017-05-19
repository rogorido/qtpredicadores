#include "dlgnuevadiocesis.h"
#include "ui_dlgnuevadiocesis.h"

dlgNuevaDiocesis::dlgNuevaDiocesis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaDiocesis)
{
    ui->setupUi(this);
}

dlgNuevaDiocesis::~dlgNuevaDiocesis()
{
    delete ui;
}
