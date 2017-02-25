#include "dlgcapitulos.h"
#include "ui_dlgcapitulos.h"

#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QDebug>

dlgCapitulos::dlgCapitulos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgCapitulos)
{
    ui->setupUi(this);

    m_capitulos = new QSqlTableModel(this);
    m_capitulos->setTable("public.capitulos");
    m_capitulos->select();

    m_resoluciones = new QSqlTableModel(this);
    m_resoluciones->setTable("public.resoluciones");
    m_resoluciones->select();

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

    // problema: este modelo no tiene buenas columnas para mostrar
    // en un tableview...
    v = {0, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    for(int n : v) {
        ui->twResoluciones->hideColumn(n);
        }

    connect(ui->twCapitulos, SIGNAL(clicked(QModelIndex)), this, SLOT(escogidoCapitulo(QModelIndex)));
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
