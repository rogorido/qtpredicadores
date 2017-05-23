#include "dlgnuevoobispo.h"
#include "ui_dlgnuevoobispo.h"

dlgNuevoObispo::dlgNuevoObispo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevoObispo)
{
    ui->setupUi(this);
}

dlgNuevoObispo::~dlgNuevoObispo()
{
    delete ui;
}
