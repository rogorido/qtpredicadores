#include "dlgobispos.h"
#include "ui_dlgobispos.h"

#include <QSqlQueryModel>
#include <QModelIndex>
#include <QMenu>
#include <QAction>
#include <QDebug>

#include "models/sqlfiltrogestor.h"

const QString sqlgeneral = "SELECT * from vistas.obispos_general";
const QString sqlvolvermirar = "bishop_id IN (SELECT bishop_id FROM bishops_details "
                               "WHERE (details->'meta_info'->>'volver_a_mirar')::boolean = TRUE)";
const QString sqlinteresante = "bishop_id IN (SELECT bishop_id FROM bishops_details "
                               "WHERE (details->'meta_info'->>'interesante')::boolean = TRUE)";

dlgObispos::dlgObispos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgObispos)
{
    ui->setupUi(this);

    obispos_model = new QSqlQueryModel(this);
    sqlactivo = sqlgeneral;

    sql_gestor = new SqlFiltroGestor(sqlgeneral, this);
    connect(sql_gestor, SIGNAL(actualizadoSqlFiltroGestor(QString)), this, SLOT(actualizarSql(QString)));

    diocesis_model = new QSqlQueryModel(this);

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

    // lo de las diócesis
    diocesis_model->setQuery("SELECT diocese_id, diocese_name FROM dioceses ORDER BY diocese_name");

    ui->cbDiocesis->setModel(diocesis_model);
    ui->cbDiocesis->setModelColumn(1);
    ui->cbDiocesis->setCurrentIndex(-1);

}

void dlgObispos::cargarMenus()
{
    menuContexto = new QMenu(this);

    a_verPersona = new QAction("Ver datos de persona", this);
    a_cambiarDiocesis = new QAction("Modificar diócesis", this);
    a_cambiarPersona = new QAction("Modificar persona", this);

    connect(a_verPersona, SIGNAL(triggered(bool)), this, SLOT(verPersona()));
    connect(a_cambiarPersona, SIGNAL(triggered(bool)), this, SLOT(modificarPersona()));
    connect(a_cambiarDiocesis, SIGNAL(triggered(bool)), this, SLOT(modificarDiocesis()));

    menuContexto->addAction(a_verPersona);
    menuContexto->addAction(a_cambiarPersona);
    menuContexto->addAction(a_cambiarDiocesis);
}

void dlgObispos::on_pbActivar_clicked()
{
    obispos_model->setQuery("SELECT * from vistas.obispos_general WHERE date_end IS NULL");
}

void dlgObispos::on_ckVolverAMirar_toggled(bool checked)
{
    if (checked)
        sql_gestor->anadirFiltro("volveramirar", sqlvolvermirar);
    else
        sql_gestor->quitarFiltro("volveramirar");
}

void dlgObispos::modificarDiocesis()
{
    qDebug() << "modificando diócesis del obispo: " << obispo_seleccionado;
}

void dlgObispos::modificarPersona()
{
    qDebug() << "modificando diócesis del obispo: " << obispo_seleccionado;
}

void dlgObispos::verPersona()
{

}

void dlgObispos::actualizarSql(QString s)
{
    sqlactivo = s;

    obispos_model->setQuery(sqlactivo);
}

void dlgObispos::on_cbDiocesis_currentIndexChanged(int index)
{
    int escogido;
    QString sql;

    QModelIndex idx = ui->cbDiocesis->model()->index(index, 0);

    if (!idx.isValid()){
        sql_gestor->quitarFiltro("diocesis");
        return;
    }

    escogido = ui->cbDiocesis->model()->data(idx).toInt();

    sql = QString("diocese_id = %1").arg(escogido);

    sql_gestor->anadirFiltro("diocesis", sql);

}

void dlgObispos::on_ckInteresante_toggled(bool checked)
{
    if (checked)
        sql_gestor->anadirFiltro("interesante", sqlinteresante);
    else
        sql_gestor->quitarFiltro("interesante");
}
