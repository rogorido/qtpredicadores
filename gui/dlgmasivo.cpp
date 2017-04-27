#include "dlgmasivo.h"
#include "ui_dlgmasivo.h"

dlgMasivo::dlgMasivo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgMasivo)
{
    ui->setupUi(this);
}

dlgMasivo::~dlgMasivo()
{
    delete ui;
}
