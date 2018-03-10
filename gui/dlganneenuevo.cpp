#include "dlganneenuevo.h"
#include "ui_dlganneenuevo.h"

dlgAnneeNuevo::dlgAnneeNuevo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgAnneeNuevo)
{
    ui->setupUi(this);
}

dlgAnneeNuevo::~dlgAnneeNuevo()
{
    delete ui;
}
