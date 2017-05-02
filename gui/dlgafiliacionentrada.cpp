#include "dlgafiliacionentrada.h"
#include "ui_dlgafiliacionentrada.h"

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

}

void dlgAfiliacionEntrada::quitarAfiliacion()
{

}

void dlgAfiliacionEntrada::aceptarAfiliaciones()
{

}

void dlgAfiliacionEntrada::anadirPersona()
{

}

void dlgAfiliacionEntrada::anadirProvincia()
{

}

void dlgAfiliacionEntrada::actualizarPersona(Persona persona)
{

}

void dlgAfiliacionEntrada::actualizarCasa(Casa casa)
{

}

void dlgAfiliacionEntrada::actualizarProvincia(Provincia provincia)
{

}
