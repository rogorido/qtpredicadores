#include "dlgpenaentrada.h"
#include "ui_dlgpenaentrada.h"

dlgPenaEntrada::dlgPenaEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgPenaEntrada)
{
    ui->setupUi(this);
}

dlgPenaEntrada::~dlgPenaEntrada()
{
    delete ui;
}
