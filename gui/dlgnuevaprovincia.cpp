#include "dlgnuevaprovincia.h"
#include "ui_dlgnuevaprovincia.h"

#include "models/provinciasmodel.h"
#include "objs/provincia.h"

dlgNuevaProvincia::dlgNuevaProvincia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaProvincia)
{
    ui->setupUi(this);

    m_provincias = ProvinciasModel::InstanceModel();

    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarProvincia()));
    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(close()));
}

dlgNuevaProvincia::~dlgNuevaProvincia()
{
    delete ui;
}

void dlgNuevaProvincia::aceptarProvincia(){
    Provincia *provincia = new Provincia();

    QString nombre = ui->txtNombre->text();
    QString notas = ui->txtNotas->toPlainText();
    QString erigida = ui->txtErigida->text();

    provincia->setNombre(nombre);
    provincia->setErigida(erigida);
    provincia->setNotas(notas);

    m_provincias->AnadirProvincia(provincia);
}
