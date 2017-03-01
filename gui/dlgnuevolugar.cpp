#include "dlgnuevolugar.h"
#include "ui_dlgnuevolugar.h"

dlgNuevoLugar::dlgNuevoLugar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevoLugar)
{
    ui->setupUi(this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
}

dlgNuevoLugar::~dlgNuevoLugar()
{
    delete ui;
}

void dlgNuevoLugar::aceptar(){

}
