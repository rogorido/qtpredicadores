#include "nuevacasa.h"
#include "ui_nuevacasa.h"

NuevaCasa::NuevaCasa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevaCasa)
{
    ui->setupUi(this);
}

NuevaCasa::~NuevaCasa()
{
    delete ui;
}
