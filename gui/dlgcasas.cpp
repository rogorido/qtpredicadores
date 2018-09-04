#include "dlgcasas.h"
#include "ui_dlgcasas.h"

#include "models/casasownmodel.h"

dlgCasas::dlgCasas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgCasas)
{
    ui->setupUi(this);
    connect(ui->btCerrar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));

    cargarModelos();
}

dlgCasas::~dlgCasas()
{
    delete ui;
}

void dlgCasas::cerrar()
{
    parentWidget()->close();
}

void dlgCasas::cargarModelos(){

    casas_model = new CasasOwnModel(this);
    casas_model->setQuery("SELECT * from vistas.houses_alternatives");

    ui->twCasas->setModel(casas_model);
    ui->twCasas->hideColumn(0);
    ui->twCasas->hideColumn(2);

    ui->twCasas->setSortingEnabled(true);
    ui->twCasas->resizeColumnsToContents();
    ui->twCasas->resizeRowsToContents();
    ui->twCasas->setAlternatingRowColors(true);
    ui->twCasas->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twCasas->horizontalHeader()->setStretchLastSection(true);

}
