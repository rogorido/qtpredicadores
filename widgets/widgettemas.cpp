#include "widgettemas.h"
#include "ui_widgettemas.h"

#include <QSortFilterProxyModel>

#include "models/temasmodel.h"

WidgetTemas::WidgetTemas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetTemas)
{
    ui->setupUi(this);

    m_temas = TemasModel::InstanceModel();

    temas_noseleccionados_proxy = new QSortFilterProxyModel(this);
    temas_noseleccionados_proxy->setSourceModel(m_temas);
    temas_noseleccionados_proxy->setFilterFixedString("0");
    temas_noseleccionados_proxy->setFilterKeyColumn(2);

    temas_seleccionados_proxy = new QSortFilterProxyModel(this);
    temas_seleccionados_proxy->setSourceModel(m_temas);
    temas_seleccionados_proxy->setFilterFixedString("1");
    temas_seleccionados_proxy->setFilterKeyColumn(2);

    ui->twNoSeleccionado->setModel(temas_noseleccionados_proxy);
    ui->twSeleccionado->setModel(temas_seleccionados_proxy);

}

WidgetTemas::~WidgetTemas()
{
    delete ui;
}
