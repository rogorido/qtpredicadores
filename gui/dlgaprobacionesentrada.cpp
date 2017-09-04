#include "dlgaprobacionesentrada.h"
#include "ui_dlgaprobacionesentrada.h"

#include <QMessageBox>

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

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
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
    if (ui->txtTipo->text().isEmpty()){
        int ret = QMessageBox::warning(this, "No hay texto en el tipo de aprobación",
                                       "Introduzca por favor texto en el tipo de aprobación");
        return;
    }

    aprobacion_activa->setTipo(ui->txtTipo->text());
    ExtraInfos e = ui->wdExtras->getExtraInfos();
    aprobacion_activa->setExtraInfos(e);

    aprobaciones_model->anadirAprobacion(aprobacion_activa);

    // borramos la aprobación activa creando un nuevo objeto
    aprobacion_activa = new Aprobacion();

    // borramos los campos
    ui->txtPersona->setText("");
    ui->txtProvincia->setText("");

    ui->wdExtras->clear();

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
    QList<Aprobacion*> lista = aprobaciones_model->getLista();

    emit(aceptarDatos(lista));

    close();
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

void dlgAprobacionesEntrada::cerrar()
{
    parentWidget()->close();
}
