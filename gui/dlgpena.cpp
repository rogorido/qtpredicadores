#include "dlgpena.h"
#include "ui_dlgpena.h"

dlgPena::dlgPena(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgPena)
{
    ui->setupUi(this);
}

dlgPena::~dlgPena()
{
    delete ui;
}
