#include "dlgnuevadiocesis.h"
#include "ui_dlgnuevadiocesis.h"

#include "models/diocesismodel.h"

dlgNuevaDiocesis::dlgNuevaDiocesis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaDiocesis)
{
    ui->setupUi(this);

    m_diocesis = DiocesisModel::InstanceModel();

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarDiocesis()));

}

dlgNuevaDiocesis::~dlgNuevaDiocesis()
{
    delete ui;
}

void dlgNuevaDiocesis::aceptarDiocesis()
{
    Diocesis *diocesis = new Diocesis();

    QString nombre = ui->txtNombre->text();
    QString nombre_latin = ui->txtNombreLatin->text();
    bool archidiocesis = ui->ckArchidiocesis->checkState();
    bool existe = ui->ckExiste->checkState();

}

void dlgNuevaDiocesis::borrarCampos()
{

}
