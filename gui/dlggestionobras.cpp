#include "dlggestionobras.h"
#include "ui_dlggestionobras.h"

dlgGestionObras::dlgGestionObras(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgGestionObras)
{
    ui->setupUi(this);
}

dlgGestionObras::~dlgGestionObras()
{
    delete ui;
}
