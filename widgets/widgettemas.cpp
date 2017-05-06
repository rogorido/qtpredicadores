#include "widgettemas.h"
#include "ui_widgettemas.h"

#include <QSortFilterProxyModel>
#include <QDebug>

#include "models/temasmodel.h"

WidgetTemas::WidgetTemas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetTemas)
{
    ui->setupUi(this);

    m_temas = TemasModel::InstanceModel();
    m_temas->sort(1, Qt::AscendingOrder);

    temas_noseleccionados_proxy = new QSortFilterProxyModel(this);
    temas_noseleccionados_proxy->setSourceModel(m_temas);
    temas_noseleccionados_proxy->setFilterFixedString("f");
    temas_noseleccionados_proxy->setFilterKeyColumn(3);

    temas_seleccionados_proxy = new QSortFilterProxyModel(this);
    temas_seleccionados_proxy->setSourceModel(m_temas);
    temas_seleccionados_proxy->setFilterFixedString("t");
    temas_seleccionados_proxy->setFilterKeyColumn(3);

    ui->twNoSeleccionado->setModel(temas_noseleccionados_proxy);
    ui->twSeleccionado->setModel(temas_seleccionados_proxy);

    ui->twNoSeleccionado->hideColumn(0);
    ui->twNoSeleccionado->hideColumn(2);
    ui->twNoSeleccionado->hideColumn(3);

    ui->twSeleccionado->hideColumn(0);
    ui->twSeleccionado->hideColumn(2);
    ui->twSeleccionado->hideColumn(3);

    ui->twNoSeleccionado->resizeColumnsToContents();
    ui->twNoSeleccionado->resizeRowsToContents();
    ui->twSeleccionado->resizeColumnsToContents();
    ui->twSeleccionado->resizeRowsToContents();

}

WidgetTemas::~WidgetTemas()
{
    delete ui;
}

void WidgetTemas::on_btAnadir_clicked()
{
    bool valor;
    QModelIndex idx = temas_noseleccionados_proxy->index(ui->twNoSeleccionado->currentIndex().row(), 3);

    if (!idx.isValid())
        return;

    valor = m_temas->data(temas_noseleccionados_proxy->mapToSource(idx), Qt::DisplayRole).toBool();
    qDebug() << "el valor es: " << valor;
    valor = !valor;
    m_temas->setData(temas_noseleccionados_proxy->mapToSource(idx), valor, Qt::EditRole);

}
