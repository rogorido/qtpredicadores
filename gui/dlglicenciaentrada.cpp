#include "dlglicenciaentrada.h"
#include "ui_dlglicenciaentrada.h"

dlgLicenciaEntrada::dlgLicenciaEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgLicenciaEntrada)
{
    ui->setupUi(this);
}

dlgLicenciaEntrada::~dlgLicenciaEntrada()
{
    delete ui;
}
