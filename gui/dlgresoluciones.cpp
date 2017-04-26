#include "dlgresoluciones.h"
#include "ui_dlgresoluciones.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>
#include <QDebug>

#include "gui/dlgseleccionargeneral.h"

DlgResoluciones::DlgResoluciones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgResoluciones)
{
    ui->setupUi(this);

    cargarModelos();
    cargarMapper();

    connect(ui->twResoluciones->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(seleccionarResolucion(QModelIndex)));
    connect(ui->btCerrar, SIGNAL(clicked()), this, SLOT(close()));
}

DlgResoluciones::~DlgResoluciones()
{
    delete ui;
}

void DlgResoluciones::seleccionarResolucion(const QModelIndex &idx)
{

    /* entiendo q con esto consigo que los campos de abajo
     * se actualicen... por que si no, ¿para qué puse esto?
     */
    mapper_data->setCurrentModelIndex(idx);

    /*
     * sacamos el índice de la columna 0 que es donde está
     * la id de la resolución, para luego convertirla en int
     * y usarla en el filtro del otro modelo.
     */
    QModelIndex indice = idx.model()->index(idx.row(), 0);
    if (!indice.isValid())
        return;

    resolucion_id = resoluciones_model->data(indice, Qt::DisplayRole).toInt();
    temas_model->setFilter(QString("resolution_id=%1").arg(resolucion_id));
}

void DlgResoluciones::recibirNuevoTema(Tema t)
{
    int tema_id = t.getId();

    QSqlQuery query;
    query.prepare("INSERT INTO resolutions_themes(theme_id, resolution_id) VALUES(:tema, :resolucion)");
    query.bindValue(":tema", tema_id);
    query.bindValue(":resolucion", resolucion_id);
    query.exec();

    temas_model->select();
    temas_model->setFilter(QString("resolution_id=%1").arg(resolucion_id));
}

void DlgResoluciones::on_btAnadirTema_clicked()
{
    dlgseleccionar = new dlgSeleccionarGeneral(TEMA, this);
    dlgseleccionar->show();

    connect(dlgseleccionar, SIGNAL(temaEscogidoSignal(Tema)), this, SLOT(recibirNuevoTema(Tema)));
}

void DlgResoluciones::cargarModelos()
{
    resoluciones_model = new QSqlQueryModel(this);
    resoluciones_model->setQuery("SELECT resolution_id, substring(resolution_text, 0, 100) || '[...]', "
                                 "chapters.general_name, small_title FROM resolutions "
                                 "JOIN chapters ON chapter=chapter_id;");
    resoluciones_model->setHeaderData(1, Qt::Horizontal, "Texto resolución");
    resoluciones_model->setHeaderData(2, Qt::Horizontal, "Capítulo");
    resoluciones_model->setHeaderData(3, Qt::Horizontal, "Epígrafe");
    ui->twResoluciones->setModel(resoluciones_model);
    ui->twResoluciones->hideColumn(0);
    ui->twResoluciones->setAlternatingRowColors(true);
    ui->twResoluciones->resizeColumnsToContents();
    ui->twResoluciones->resizeRowsToContents();
    ui->twResoluciones->horizontalHeader()->setStretchLastSection(true);
    ui->twResoluciones->setSortingEnabled(true);
    ui->twResoluciones->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twResoluciones->setSelectionMode(QAbstractItemView::SingleSelection);

    temas_model = new QSqlRelationalTableModel(this);
    temas_model->setTable("chapters.resolutions_themes");
    temas_model->setRelation(1, QSqlRelation("general.themes", "theme_id", "theme"));
    temas_model->setHeaderData(1, Qt::Horizontal, "Tema");
    temas_model->select();
    ui->twTemas->setModel(temas_model);
    ui->twTemas->hideColumn(0);
    ui->twTemas->hideColumn(2);
    ui->twTemas->horizontalHeader()->setStretchLastSection(true);
    ui->twTemas->setAlternatingRowColors(true);
    ui->twTemas->resizeColumnsToContents();
    ui->twTemas->resizeRowsToContents();
    ui->twTemas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twTemas->setSelectionMode(QAbstractItemView::SingleSelection);

}

void DlgResoluciones::cargarMapper()
{
    mapper_data = new QDataWidgetMapper(this);
    mapper_data->setModel(resoluciones_model);
    mapper_data->addMapping(ui->txtResolucion, 1);

}
