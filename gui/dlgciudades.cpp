#include "dlgciudades.h"
#include "ui_dlgciudades.h"

#include <QSqlTableModel>

dlgCiudades::dlgCiudades(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgCiudades)
{
    ui->setupUi(this);

    connect(ui->btCerrar, SIGNAL(clicked(bool)), this, SLOT(close()));

    cargarModelos();
}

dlgCiudades::~dlgCiudades()
{
    delete ui;
}

void dlgCiudades::cargarModelos()
{
    /*
     * realmente tvz se podría hacer con un Qsqltablemodel
     * y luego usar un proxy para filtrarlo, pero por ahora paso
     */
    ciudades_model = new QSqlTableModel(this);
    ciudades_model->setTable("general.places");
    ciudades_model->setHeaderData(1, Qt::Horizontal, "Nombre");
    ciudades_model->setHeaderData(2, Qt::Horizontal, "Latín");
    ciudades_model->setHeaderData(3, Qt::Horizontal, "Otros nombres");
    ciudades_model->setHeaderData(4, Qt::Horizontal, "Wikidata");
    ciudades_model->setHeaderData(5, Qt::Horizontal, "Latitud");
    ciudades_model->setHeaderData(6, Qt::Horizontal, "Longitud");
    ciudades_model->setHeaderData(7, Qt::Horizontal, "País");
    ciudades_model->setSort(1, Qt::AscendingOrder);
    ciudades_model->select();

    ui->twCiudades->setModel(ciudades_model);
    ui->twCiudades->setSortingEnabled(true);
    ui->twCiudades->resizeColumnsToContents();
    ui->twCiudades->resizeRowsToContents();
    ui->twCiudades->setAlternatingRowColors(true);
    ui->twCiudades->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twCiudades->horizontalHeader()->setStretchLastSection(true);
    ui->twCiudades->hideColumn(0);
    ui->twCiudades->hideColumn(8);
    ui->twCiudades->hideColumn(9);
    ui->twCiudades->hideColumn(10); // other_data

}
