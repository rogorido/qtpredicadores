#include "dlgobispos.h"
#include "ui_dlgobispos.h"

#include <QSqlQueryModel>
#include <QModelIndex>
#include <QMenu>
#include <QAction>
#include <QDebug>

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
    cargarMenus();

    ui->twObispos->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->twObispos->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(seleccionarObispo(QModelIndex)));
    connect(ui->twObispos, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(menuContextual(const QPoint &)));
}

dlgObispos::~dlgObispos()
{
    delete ui;
}

void dlgObispos::seleccionarObispo(const QModelIndex &idx)
{
    /*
     * sacamos el índice de la columna 0 que es donde está
     * la id de la resolución, para luego convertirla en int
     * y usarla en el filtro del otro modelo.
     */
    QModelIndex indice = idx.model()->index(idx.row(), 0);
    if (!indice.isValid())
        return;

    obispo_seleccionado = obispos_model->data(indice, Qt::DisplayRole).toInt();

    qDebug() << "el id es: " << obispo_seleccionado;
}

void dlgObispos::menuContextual(const QPoint &point)
{
    qDebug() << "estamos en el menú";

    menuContexto->popup(ui->twObispos->viewport()->mapToGlobal(point));
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

    cambiarDiocesis = new QAction("Modificar diócesis", this);
    cambiarPersona = new QAction("Modificar persona", this);

    connect(cambiarPersona, SIGNAL(triggered(bool)), this, SLOT(modificarPersona()));
    connect(cambiarDiocesis, SIGNAL(triggered(bool)), this, SLOT(modificarDiocesis()));

    menuContexto->addAction(cambiarPersona);
    menuContexto->addAction(cambiarDiocesis);
}

void dlgObispos::on_pbActivar_clicked()
{
    obispos_model->setQuery("SELECT * from vistas.obispos_general WHERE date_end IS NULL");
}

void dlgObispos::on_ckVolverAMirar_toggled(bool checked)
{
    if (checked){
        sqlactivo = sqlgeneral + " WHERE bishop_id IN (" + sqlvolvermirar + ")";
    }
    else
        sqlactivo = sqlgeneral;

    obispos_model->setQuery(sqlactivo);
}

void dlgObispos::modificarDiocesis()
{
    qDebug() << "modificando diócesis del obispo: " << obispo_seleccionado;
}

void dlgObispos::modificarPersona()
{
    qDebug() << "modificando diócesis del obispo: " << obispo_seleccionado;
}

