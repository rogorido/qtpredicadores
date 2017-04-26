#include "dlgresoluciones.h"
#include "ui_dlgresoluciones.h"

DlgResoluciones::DlgResoluciones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgResoluciones)
{
    ui->setupUi(this);
}

DlgResoluciones::~DlgResoluciones()
{
    delete ui;
}
