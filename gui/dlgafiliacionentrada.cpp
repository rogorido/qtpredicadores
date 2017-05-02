#include "dlgafiliacionentrada.h"
#include "ui_dlgafiliacionentrada.h"

dlgAfiliacionEntrada::dlgAfiliacionEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgAfiliacionEntrada)
{
    ui->setupUi(this);
}

dlgAfiliacionEntrada::~dlgAfiliacionEntrada()
{
    delete ui;
}
