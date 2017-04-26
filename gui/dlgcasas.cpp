#include "dlgcasas.h"
#include "ui_dlgcasas.h"

#include <QSqlRelationalTableModel>

dlgCasas::dlgCasas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgCasas)
{
    ui->setupUi(this);
    connect(ui->btCerrar, SIGNAL(clicked(bool)), this, SLOT(close()));

    cargarModelos();
}

dlgCasas::~dlgCasas()
{
    delete ui;
}

void dlgCasas::cargarModelos(){

    casas_model = new QSqlRelationalTableModel(this);
    casas_model->setTable("general.houses");
    casas_model->setRelation(4, QSqlRelation("general.places", "place_id", "place"));
    casas_model->setRelation(12, QSqlRelation("general.provinces", "province_id", "name"));
    casas_model->setHeaderData(1, Qt::Horizontal, "Nombre");
    casas_model->setHeaderData(2, Qt::Horizontal, "Latín");
    casas_model->setHeaderData(3, Qt::Horizontal, "Otros nombres");
    casas_model->setHeaderData(4, Qt::Horizontal, "Lugar");
    casas_model->setHeaderData(12, Qt::Horizontal, "Provincia");
    casas_model->setHeaderData(13, Qt::Horizontal, "Diócesis");
    casas_model->setHeaderData(14, Qt::Horizontal, "Fecha");
    casas_model->setSort(1, Qt::AscendingOrder);
    casas_model->select();

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
