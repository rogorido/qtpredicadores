#include "dlgcasas.h"
#include "ui_dlgcasas.h"

#include "models/casasownmodel.h"
//#include <QSqlRelationalTableModel>

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
    casas_model->setQuery("SELECT * from general.houses");

    ui->twCasas->setModel(casas_model);
    ui->twCasas->hideColumn(0);
    ui->twCasas->hideColumn(2);
    ui->twCasas->hideColumn(3);
    ui->twCasas->hideColumn(5);
    ui->twCasas->hideColumn(6);
    ui->twCasas->hideColumn(7);
    ui->twCasas->hideColumn(8);
    ui->twCasas->hideColumn(9);
    ui->twCasas->hideColumn(10);
    ui->twCasas->hideColumn(11);
    ui->twCasas->hideColumn(16);
    ui->twCasas->hideColumn(17);

    ui->twCasas->setSortingEnabled(true);
    ui->twCasas->resizeColumnsToContents();
    ui->twCasas->resizeRowsToContents();
    ui->twCasas->setAlternatingRowColors(true);
    ui->twCasas->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twCasas->horizontalHeader()->setStretchLastSection(true);

}
