#include "dlgobispos.h"
#include "ui_dlgobispos.h"

#include <QSqlQueryModel>
#include <QModelIndex>

const QString sqlgeneral = "SELECT * from vistas.obispos_general";
const QString sqlvolvermirar = "SELECT bishop_id FROM bishops_details "
                               "WHERE (details->'meta_info'->>'volver_a_mirar')::boolean = TRUE";

dlgObispos::dlgObispos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgObispos)
{
    ui->setupUi(this);

    obispos_model = new QSqlQueryModel(this);
    sqlactivo = sqlgeneral;
    cargarModelos();
}

dlgObispos::~dlgObispos()
{
    delete ui;
}

void dlgObispos::cargarModelos()
{
    obispos_model->setQuery(sqlactivo);

    ui->twObispos->setModel(obispos_model);

    ui->twObispos->hideColumn(0);
    ui->twObispos->setAlternatingRowColors(true);
    //ui->twResoluciones->setColumnWidth(1, 80);
    //ui->twResoluciones->resizeColumnsToContents();
    //ui->twResoluciones->resizeRowsToContents();
    ui->twObispos->horizontalHeader()->setStretchLastSection(true);
    ui->twObispos->setSortingEnabled(true);
    ui->twObispos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twObispos->setSelectionMode(QAbstractItemView::SingleSelection);

    // escogemos la primera línea del modelo...
    QModelIndex index = obispos_model->index(0,0);
    if (index.isValid()) {
        ui->twObispos->setCurrentIndex(index);
    }
}
