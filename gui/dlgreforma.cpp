#include "dlgreforma.h"
#include "ui_dlgreforma.h"

#include "gui/dlgseleccionargeneral.h"

dlgReforma::dlgReforma(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgReforma)
{
    ui->setupUi(this);

    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->txtLugar, SIGNAL(dobleclick()), this, SLOT(anadirLugar()));
    connect(ui->btOk, SIGNAL(clicked()), this, SLOT(aceptar()));

}

dlgReforma::~dlgReforma()
{
    delete ui;
}

void dlgReforma::anadirLugar()
{
    dlgSeleccionarGeneral *dlgSeleccionar = new dlgSeleccionarGeneral(LUGAR, this);
    dlgSeleccionar->show();

    connect(dlgSeleccionar, SIGNAL(lugarEscogidoSignal(Lugar)), this, SLOT(recibirLugar(Lugar)));
}

void dlgReforma::quitarLugar()
{
    lugar_struct = elementopareado();
    ui->txtLugar->clear();
}

void dlgReforma::aceptar()
{

}

void dlgReforma::recibirLugar(Lugar lugar)
{
    lugar_struct.id = lugar.getId();
    lugar_struct.elemento = lugar.getLugar();

    ui->txtLugar->setText(lugar_struct.elemento);
}
