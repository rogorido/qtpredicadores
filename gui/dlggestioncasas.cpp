#include "dlggestioncasas.h"
#include "ui_dlggestioncasas.h"

#include "models/casasmodel.h"

dlgGestionCasas::dlgGestionCasas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgGestionCasas)
{
    ui->setupUi(this);
    connect(ui->btCerrar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));

    cargarModelos();
}

dlgGestionCasas::~dlgGestionCasas()
{
    delete ui;
}

void dlgGestionCasas::cerrar()
{
    parentWidget()->close();
}

void dlgGestionCasas::cargarModelos(){

    casas_model = CasasModel::InstanceModel();
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
