#include "dlgdetalles.h"
#include "ui_dlgdetalles.h"

#include "objs/jsongestor.h"
#include "dlgseleccionarpersona.h"

dlgDetalles::dlgDetalles(JsonGestor *json, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgDetalles), jsondetalles(json)
{
    ui->setupUi(this);
    jsondetalles->setTreeWidget(ui->twDetalles);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(hide()));

}

dlgDetalles::~dlgDetalles()
{
    delete ui;
}

void dlgDetalles::recibirPersona(Persona persona){
    int id;
    QString valor;

    id = persona.getId();
    valor = persona.getNombre() + ' ' + persona.getApellidos();

    jsondetalles->anadirValor("Persona", valor, id);
}


void dlgDetalles::on_btPersona_clicked()
{
    dlgSeleccionarPersona *dlgPersona = new dlgSeleccionarPersona(this);
    dlgPersona->show();

    connect(dlgPersona, SIGNAL(personaEscogida(Persona)), this, SLOT(recibirPersona(Persona)));

}
