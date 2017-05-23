#include "dlgfuenteentrada.h"
#include "ui_dlgfuenteentrada.h"

dlgFuenteEntrada::dlgFuenteEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgFuenteEntrada)
{
    ui->setupUi(this);
}

dlgFuenteEntrada::~dlgFuenteEntrada()
{
    delete ui;
}
