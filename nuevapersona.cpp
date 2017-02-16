#include "nuevapersona.h"
#include "ui_nuevapersona.h"

NuevaPersona::NuevaPersona(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevaPersona)
{
    ui->setupUi(this);
}

NuevaPersona::~NuevaPersona()
{
    delete ui;
}
