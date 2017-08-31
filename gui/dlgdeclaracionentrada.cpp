#include "dlgdeclaracionentrada.h"
#include "ui_dlgdeclaracionentrada.h"

#include "gui/dlgpenaentrada.h"

// TODO: falta añadir lo de dlginfraccionentrada.h

// TODO: falta añadir lo de persona, pero no sé para qué lo puse...

dlgDeclaracionEntrada::dlgDeclaracionEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgDeclaracionEntrada)
{
    ui->setupUi(this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->btPena, SIGNAL(clicked(bool)), this, SLOT(anadirPena()));
    connect(ui->wdNotas, SIGNAL(textoIntroducido()), this, SLOT(notaIntroducida()));
}

dlgDeclaracionEntrada::~dlgDeclaracionEntrada()
{
    delete ui;
}

void dlgDeclaracionEntrada::aceptar()
{
    QString tipo = ui->txtTipo->text();
    ExtraInfos e = ui->wdExtras->getExtraInfos();

    declaracion.setPena(pena_estipulada);
    declaracion.setTipo(tipo);
    declaracion.setExtraInfos(e);

    emit(aceptarDeclaracion(declaracion));

    close();
}

void dlgDeclaracionEntrada::anadirInfraccion()
{

}

void dlgDeclaracionEntrada::anadirPena()
{
    dlgPenaEntrada *dlgpena = new dlgPenaEntrada(this);
    dlgpena->show();

    connect(dlgpena, SIGNAL(aceptarPena(Pena)), this, SLOT(recibirPena(Pena)));
}

void dlgDeclaracionEntrada::recibirInfraccion(Infraccion infraccion)
{

}

void dlgDeclaracionEntrada::recibirPena(Pena pena)
{
    pena_estipulada = pena;

}
