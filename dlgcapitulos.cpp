#include "dlgcapitulos.h"
#include "ui_dlgcapitulos.h"

DlgCapitulos::DlgCapitulos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgCapitulos)
{
    ui->setupUi(this);
}

DlgCapitulos::~DlgCapitulos()
{
    delete ui;
}
