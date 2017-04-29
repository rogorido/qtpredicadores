#include "dlgaprobacionesentrada.h"
#include "ui_dlgaprobacionesentrada.h"

#include "gui/dlgseleccionargeneral.h"

dlgAprobacionesEntrada::dlgAprobacionesEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgAprobacionesEntrada)
{
    ui->setupUi(this);

    aprobacion_activa = new Aprobacion();

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btPersona, SIGNAL(clicked(bool)), this, SLOT(anadirPersona()));
    connect(ui->btProvincia, SIGNAL(clicked(bool)), this, SLOT(anadirProvincia()));
    connect(ui->btAnadirAprobacion, SIGNAL(clicked(bool)), this, SLOT(anadirAprobacion()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarAprobaciones()));

}

dlgAprobacionesEntrada::~dlgAprobacionesEntrada()
{
    delete ui;
}

void dlgAprobacionesEntrada::anadirAprobacion()
{

}

void dlgAprobacionesEntrada::aceptarAprobaciones()
{

}

void dlgAprobacionesEntrada::anadirPersona()
{

}

void dlgAprobacionesEntrada::anadirProvincia()
{

}

void dlgAprobacionesEntrada::actualizarPersona(Persona persona)
{

}

void dlgAprobacionesEntrada::actualizarProvincia(Provincia provincia)
{

}
