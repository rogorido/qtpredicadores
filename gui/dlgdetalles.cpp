#include "dlgdetalles.h"
#include "ui_dlgdetalles.h"

#include "objs/jsongestor.h"
#include "objs/persona.h"
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


void dlgDetalles::on_btPersona_clicked()
{
    dlgSeleccionarPersona dlgPersona;


}
