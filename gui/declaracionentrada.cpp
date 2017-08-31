#include "declaracionentrada.h"
#include "ui_declaracionentrada.h"

#include "gui/dlgpenaentrada.h"

// TODO: falta añadir lo de dlginfraccionentrada.h

DeclaracionEntrada::DeclaracionEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeclaracionEntrada)
{
    ui->setupUi(this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->btPena, SIGNAL(clicked(bool)), this, SLOT(anadirPena()));
    connect(ui->wdNotas, SIGNAL(textoIntroducido()), this, SLOT(notaIntroducida()));
}

DeclaracionEntrada::~DeclaracionEntrada()
{
    delete ui;
}

void DeclaracionEntrada::aceptar()
{

}

void DeclaracionEntrada::anadirInfraccion()
{

}

void DeclaracionEntrada::anadirPena()
{
    dlgPenaEntrada *dlgpena = new dlgPenaEntrada(this);
    dlgpena->show();

    connect(dlgpena, SIGNAL(aceptarPena(Pena)), this, SLOT(recibirPena(Pena)));
}

void DeclaracionEntrada::recibirInfraccion(Infraccion infraccion)
{

}

void DeclaracionEntrada::recibirPena(Pena pena)
{
    pena_estipulada = pena;

}
