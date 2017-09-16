#include "dlgobispos.h"
#include "ui_dlgobispos.h"

#include <QSqlQueryModel>
#include <QModelIndex>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QPoint>

#include "objs/obispo.h"

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

    connect(ui->twObispos, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(mostrarCustomMenu(QPoint)));
    //connect(ui->twObispos->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(seleccionadoObispo(QModelIndex)));

    cargarMenus();
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

void dlgObispos::cargarMenus()
{
    menuContexto = new QMenu(this);

    cambiarDiocesis = new QAction("Modificar diócesis");
    cambiarPersona = new QAction("Modificar persona");

    connect(cambiarPersona, SIGNAL(triggered(bool)), this, SLOT(modificarPersona()));
    connect(cambiarDiocesis, SIGNAL(triggered(bool)), this, SLOT(modificarDiocesis()));

    menuContexto->addAction(cambiarPersona);
    menuContexto->addAction(cambiarDiocesis);
}

void dlgObispos::on_ckVolverAMirar_toggled(bool checked)
{
    if (checked){
        volveramirar = true;
        sqlactivo = sqlgeneral + " WHERE vistas.obispos_general.bishop_id IN (" + sqlvolvermirar + ")";
    }
    else {
        volveramirar = false;
        sqlactivo = sqlgeneral;
    }

    obispos_model->setQuery(sqlactivo);
}

void dlgObispos::mostrarCustomMenu(QPoint pos)
{
    menuContexto->show();

}

void dlgObispos::seleccionadoObispo(const QModelIndex &idx)
{
    if (!idx.isValid())
        return;

    /*
     * sacamos el índice de la columna 0 que es donde está
     * la id de la resolución, para luego convertirla en int
     * y usarla en el filtro del otro modelo.
     */
    QModelIndex indice = idx.model()->index(idx.row(), 0);
    if (!indice.isValid())
        return;

    obispo_seleccionado = obispos_model->data(indice, Qt::DisplayRole).toInt();

}

void dlgObispos::modificarDiocesis()
{
    qDebug() << "modificando diócesis del obispo: " << obispo_seleccionado;
}

void dlgObispos::modificarPersona()
{
    qDebug() << "modificando diócesis del obispo: " << obispo_seleccionado;
}

