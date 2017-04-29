#include "dlgaprobacionesentrada.h"
#include "ui_dlgaprobacionesentrada.h"

#include "gui/dlgseleccionargeneral.h"

dlgAprobacionesEntrada::dlgAprobacionesEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgAprobacionesEntrada)
{
    ui->setupUi(this);

    aprobacion_activa = new Aprobacion();
    aprobaciones_model = new AprobacionesTableModel(this);

    ui->twAprobaciones->setModel(aprobaciones_model);
    ui->twAprobaciones->setAlternatingRowColors(true);
    ui->twAprobaciones->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twAprobaciones->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twAprobaciones->horizontalHeader()->setStretchLastSection(true);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btPersona, SIGNAL(clicked(bool)), this, SLOT(anadirPersona()));
    connect(ui->btProvincia, SIGNAL(clicked(bool)), this, SLOT(anadirProvincia()));
    connect(ui->btAnadirAprobacion, SIGNAL(clicked(bool)), this, SLOT(anadirAprobacion()));
    connect(ui->btQuitarAprobacion, SIGNAL(clicked(bool)), this, SLOT(quitarAprobacion()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarAprobaciones()));

}

dlgAprobacionesEntrada::~dlgAprobacionesEntrada()
{
    delete ui;
}

void dlgAprobacionesEntrada::anadirAprobacion()
{

    aprobaciones_model->anadirAprobacion(aprobacion_activa);

    aprobacion_activa = new Aprobacion();
    ui->txtPersona->setText("");
    ui->txtProvincia->setText("");
    ui->twAprobaciones->resizeColumnsToContents();
    ui->twAprobaciones->resizeRowsToContents();
}

void dlgAprobacionesEntrada::quitarAprobacion()
{
    QModelIndex idx = ui->twAprobaciones->currentIndex();

    if (!idx.isValid())
        return;

    int row = idx.row();
    aprobaciones_model->quitarAprobacion(row);
}

void dlgAprobacionesEntrada::aceptarAprobaciones()
{

}

void dlgAprobacionesEntrada::anadirPersona()
{
    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(PERSONA, this);
    dlgseleccionar->show();

    connect(dlgseleccionar, SIGNAL(personaEscogidaSignal(Persona)), this, SLOT(actualizarPersona(Persona)));

}

void dlgAprobacionesEntrada::anadirProvincia()
{

    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(PROVINCIA, this);
    dlgseleccionar->show();

    connect(dlgseleccionar, SIGNAL(provinciaEscogidaSignal(Provincia)), this, SLOT(actualizarProvincia(Provincia)));

}

void dlgAprobacionesEntrada::actualizarPersona(Persona persona)
{

    aprobacion_activa->setPersona(persona);
    QString nombre_persona;

    nombre_persona = persona.getNombre() + ' ' + persona.getApellidos() + ' ' + persona.getOrigen();

    ui->txtPersona->setText(nombre_persona);
}

void dlgAprobacionesEntrada::actualizarProvincia(Provincia provincia)
{
    aprobacion_activa->setProvincia(provincia);

    ui->txtProvincia->setText(provincia.getNombre());
}
