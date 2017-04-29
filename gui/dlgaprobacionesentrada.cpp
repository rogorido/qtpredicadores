#include "dlgaprobacionesentrada.h"
#include "ui_dlgaprobacionesentrada.h"

dlgAprobacionesEntrada::dlgAprobacionesEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgAprobacionesEntrada)
{
    ui->setupUi(this);
}

dlgAprobacionesEntrada::~dlgAprobacionesEntrada()
{
    delete ui;
}
