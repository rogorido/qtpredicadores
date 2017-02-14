#include "nuevaresolucion.h"
#include "ui_nuevaresolucion.h"

NuevaResolucion::NuevaResolucion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevaResolucion)
{
    ui->setupUi(this);
}

NuevaResolucion::~NuevaResolucion()
{
    delete ui;
}
