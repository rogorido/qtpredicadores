#include "dlgnuevamisionfilipinas.h"
#include "ui_dlgnuevamisionfilipinas.h"

dlgNuevaMisionFilipinas::dlgNuevaMisionFilipinas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaMisionFilipinas)
{
    ui->setupUi(this);
}

dlgNuevaMisionFilipinas::~dlgNuevaMisionFilipinas()
{
    delete ui;
}
