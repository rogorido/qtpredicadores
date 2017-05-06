#include "dlgsufragiosentrada.h"
#include "ui_dlgsufragiosentrada.h"

dlgSufragiosEntrada::dlgSufragiosEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSufragiosEntrada)
{
    ui->setupUi(this);
}

dlgSufragiosEntrada::~dlgSufragiosEntrada()
{
    delete ui;
}
