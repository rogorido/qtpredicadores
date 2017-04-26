#include "dlgcasas.h"
#include "ui_dlgcasas.h"

dlgCasas::dlgCasas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgCasas)
{
    ui->setupUi(this);
}

dlgCasas::~dlgCasas()
{
    delete ui;
}
