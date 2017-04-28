#include "dlgcapitulos.h"
#include "ui_dlgcapitulos.h"

#include "models/capitulosmodel.h"
#include "gui/dlgmasivo.h"

#include <QDebug>

dlgCapitulos::dlgCapitulos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgCapitulos)
{
    ui->setupUi(this);

    m_capitulos = CapitulosModel::InstanceModel();

    // atención: esto da un error al cerrar la aplicación!
    //m_proxyresoluciones = new QSortFilterProxyModel(this);
    //m_proxyresoluciones->setSourceModel(m_resoluciones);

    ui->twCapitulos->setModel(m_capitulos);
    //ui->twResoluciones->setModel(m_proxyresoluciones);

    // esto es para hacer el loop de un array de ints...
    // la finalidad: ocultar algunas columnas
    std::vector<int> v = {0, 2, 6, 7, 8, 9, 10, 11, 12};
    for(int n : v) {
        ui->twCapitulos->hideColumn(n);
        }

    m_capitulos->setHeaderData(1, Qt::Horizontal, "Nombre general");
    m_capitulos->setHeaderData(2, Qt::Horizontal, "Fecha inicio");
    m_capitulos->setHeaderData(3, Qt::Horizontal, "Fecha final");
    m_capitulos->setHeaderData(4, Qt::Horizontal, "Tipo");
    m_capitulos->setHeaderData(13, Qt::Horizontal, "Definitorio");

    ui->twCapitulos->setAlternatingRowColors(true);
    ui->twCapitulos->resizeColumnsToContents();
    ui->twCapitulos->resizeRowsToContents();
    ui->twCapitulos->horizontalHeader()->setStretchLastSection(true);
    ui->twCapitulos->setSortingEnabled(true);
    ui->twCapitulos->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->twCapitulos, SIGNAL(clicked(QModelIndex)), this, SLOT(escogidoCapitulo(QModelIndex)));
    connect(ui->btCerrar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btIntroducirAsistentes, SIGNAL(clicked(bool)), this, SLOT(introducirAsistentes()));
    // no reconoce esta signal... esto parece que lo han cambiado.
    //connect(ui->twCapitulos, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(escogidoCapitulo(QModelIndex)));

}

dlgCapitulos::~dlgCapitulos()
{
    delete ui;
}

void dlgCapitulos::escogidoCapitulo(const QModelIndex &idx){
    /* sacamos el id */
    QModelIndex indice = idx.model()->index(idx.row(), 0);
    int id = m_capitulos->data(indice, Qt::DisplayRole).toInt();


}

void dlgCapitulos::introducirAsistentes()
{
    QModelIndex indice = m_capitulos->index(ui->twCapitulos->currentIndex().row(), 0);

    if (!indice.isValid())
        return;

    int id = m_capitulos->data(indice, Qt::DisplayRole).toInt();

    dlgmasivo = new dlgMasivo(id, this);
    dlgmasivo->show();

}
