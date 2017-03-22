#include "dlgtemas.h"
#include "ui_dlgtemas.h"

dlgTemas::dlgTemas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgTemas)
{
    ui->setupUi(this);
}

dlgTemas::~dlgTemas()
{
    delete ui;
}
