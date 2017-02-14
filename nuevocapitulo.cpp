#include "nuevocapitulo.h"
#include "ui_nuevocapitulo.h"

NuevoCapitulo::NuevoCapitulo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NuevoCapitulo)
{
    ui->setupUi(this);
}

NuevoCapitulo::~NuevoCapitulo()
{
    delete ui;
}
