#include "dlglicenciaentrada.h"
#include "ui_dlglicenciaentrada.h"

dlgLicenciaEntrada::dlgLicenciaEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgLicenciaEntrada)
{
    ui->setupUi(this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));

    cargarModelos();
}

dlgLicenciaEntrada::~dlgLicenciaEntrada()
{
    delete ui;
}

void dlgLicenciaEntrada::aceptar()
{
    licencia_activa.setLicenciaTipo(ui->txtTipo->text());
    licencia_activa.setOtorgantes(otorgantes);
    licencia_activa.setReceptores(receptores);
    licencia_activa.setAsunto(ui->txtAsunto->text());
    licencia_activa.setSeguridad(ui->spSeguridad->value());

    emit(aceptarLicencia(licencia_activa));

    close();
}

void dlgLicenciaEntrada::anadirReceptor()
{

}

void dlgLicenciaEntrada::quitarReceptor()
{

}

void dlgLicenciaEntrada::anadirOtorgante()
{

}

void dlgLicenciaEntrada::quitarOtorgante()
{

}

void dlgLicenciaEntrada::cargarModelos()
{

}
