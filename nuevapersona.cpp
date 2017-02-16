#include "nuevapersona.h"
#include "ui_nuevapersona.h"

NuevaPersona::NuevaPersona(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevaPersona)
{
    ui->setupUi(this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarPersona()));

}

NuevaPersona::~NuevaPersona()
{
    delete ui;
}

void NuevaPersona::aceptarPersona(){

}
