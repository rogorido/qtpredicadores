#include "dlgestadisticas.h"
#include "ui_dlgestadisticas.h"

dlgEstadisticas::dlgEstadisticas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgEstadisticas)
{
    ui->setupUi(this);
}

dlgEstadisticas::~dlgEstadisticas()
{
    delete ui;
}
