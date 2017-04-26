#include "dlgresoluciones.h"
#include "ui_dlgresoluciones.h"

#include <QSqlQueryModel>
#include <QDataWidgetMapper>

DlgResoluciones::DlgResoluciones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgResoluciones)
{
    ui->setupUi(this);

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

    mapper_data = new QDataWidgetMapper(this);
    mapper_data->setModel(resoluciones_model);

    mapper_data->addMapping(ui->txtResolucion, 1);

    connect(ui->twResoluciones->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(seleccionarResolucion(QModelIndex)));
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
}
