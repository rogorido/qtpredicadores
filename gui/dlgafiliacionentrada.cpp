#include "dlgafiliacionentrada.h"
#include "ui_dlgafiliacionentrada.h"

#include <QMessageBox>

#include "gui/dlgseleccionargeneral.h"

dlgAfiliacionEntrada::dlgAfiliacionEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgAfiliacionEntrada)
{
    ui->setupUi(this);

    afiliacion_activa = new Afiliacion();
    afiliaciones_model = new AfiliacionesTableModel(this);

    ui->twAfiliaciones->setModel(afiliaciones_model);
    ui->twAfiliaciones->setAlternatingRowColors(true);
    ui->twAfiliaciones->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twAfiliaciones->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twAfiliaciones->horizontalHeader()->setStretchLastSection(true);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btPersona, SIGNAL(clicked(bool)), this, SLOT(anadirPersona()));
    connect(ui->btProvinciaOrigen, SIGNAL(clicked(bool)), this, SLOT(anadirProvinciaOrigen()));
    connect(ui->btProvinciaDestino, SIGNAL(clicked(bool)), this, SLOT(anadirProvinciaDestino()));
    connect(ui->btCasaOrigen, SIGNAL(clicked(bool)), this, SLOT(anadirCasaOrigen()));
    connect(ui->btCasaDestino, SIGNAL(clicked(bool)), this, SLOT(anadirCasaDestino()));
    connect(ui->btAnadirAfiliacion, SIGNAL(clicked(bool)), this, SLOT(anadirAfiliacion()));
    connect(ui->btQuitarAfiliacion, SIGNAL(clicked(bool)), this, SLOT(quitarAfiliacion()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarAfiliaciones()));
}

dlgAfiliacionEntrada::~dlgAfiliacionEntrada()
{
    delete ui;
}

void dlgAfiliacionEntrada::anadirAfiliacion()
{
    if (ui->txtPersona->text().isEmpty()){
        int ret = QMessageBox::warning(this, "No hay persona escogida",
                                       "Introduzca por favor una persona.");
        return;
    }

    ExtraInfos e = ui->wdExtraInfos->getExtraInfos();
    afiliacion_activa->setExtras(e);

    afiliaciones_model->anadirAfiliacion(afiliacion_activa);

    // borramos la aprobación activa creando un nuevo objeto
    afiliacion_activa = new Afiliacion();

    // borramos los campos
    ui->txtPersona->setText("");
    ui->txtProvinciaOrigen->setText("");
    ui->txtProvinciaDestino->setText("");
    ui->txtCasaOrigen->setText("");
    ui->txtCasaDestino->setText("");

    ui->wdExtraInfos->clear();

    ui->twAfiliaciones->resizeColumnsToContents();
    ui->twAfiliaciones->resizeRowsToContents();
}

void dlgAfiliacionEntrada::quitarAfiliacion()
{

}

void dlgAfiliacionEntrada::aceptarAfiliaciones()
{

}

void dlgAfiliacionEntrada::anadirPersona()
{
    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(PERSONA, this);
    dlgseleccionar->show();

    connect(dlgseleccionar, SIGNAL(personaEscogidaSignal(Persona)), this, SLOT(actualizarPersona(Persona)));

}

void dlgAfiliacionEntrada::anadirCasaOrigen()
{
    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(CASA, this);
    dlgseleccionar->show();

    connect(dlgseleccionar, SIGNAL(casaEscogidaSignal(Casa)), this, SLOT(actualizarCasaOrigen(Casa)));

}

void dlgAfiliacionEntrada::anadirCasaDestino()
{
    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(CASA, this);
    dlgseleccionar->show();

    connect(dlgseleccionar, SIGNAL(casaEscogidaSignal(Casa)), this, SLOT(actualizarCasaDestino(Casa)));

}

void dlgAfiliacionEntrada::anadirProvinciaOrigen()
{
    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(PROVINCIA, this);
    dlgseleccionar->show();

    connect(dlgseleccionar, SIGNAL(provinciaEscogidaSignal(Provincia)), this, SLOT(actualizarProvinciaOrigen(Provincia)));

}

void dlgAfiliacionEntrada::anadirProvinciaDestino()
{
    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(PROVINCIA, this);
    dlgseleccionar->show();

    connect(dlgseleccionar, SIGNAL(provinciaEscogidaSignal(Provincia)), this, SLOT(actualizarProvinciaDestino(Provincia)));

}

void dlgAfiliacionEntrada::actualizarPersona(Persona persona)
{
    afiliacion_activa->setPersona(persona);
    QString nombre_persona;

    nombre_persona = persona.getNombre() + ' ' + persona.getApellidos() + ' ' + persona.getOrigen();

    ui->txtPersona->setText(nombre_persona);
}

void dlgAfiliacionEntrada::actualizarProvinciaOrigen(Provincia provincia)
{
    afiliacion_activa->setProvinciaOrigen(provincia);

    ui->txtProvinciaOrigen->setText(provincia.getNombre());
}

void dlgAfiliacionEntrada::actualizarCasaOrigen(Casa casa)
{
    afiliacion_activa->setCasaOrigen(casa);

    ui->txtCasaOrigen->setText(casa.getNombre());

}

void dlgAfiliacionEntrada::actualizarCasaDestino(Casa casa)
{
    afiliacion_activa->setCasaDestino(casa);

    ui->txtCasaDestino->setText(casa.getNombre());
}

void dlgAfiliacionEntrada::actualizarProvinciaDestino(Provincia provincia)
{
    afiliacion_activa->setProvinciaDestino(provincia);

    ui->txtProvinciaDestino->setText(provincia.getNombre());

}
