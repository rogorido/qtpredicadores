#include "dlgviajeentrada.h"
#include "ui_dlgviajeentrada.h"

dlgViajeEntrada::dlgViajeEntrada(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgViajeEntrada)
{
    ui->setupUi(this);
}

dlgViajeEntrada::~dlgViajeEntrada()
{
    delete ui;
}
