#include "dlgmisiones.h"
#include "ui_dlgmisiones.h"

#include <QModelIndex>
#include <QMdiSubWindow>
#include <QSqlTableModel>

#include "gui/dlgnuevapersona.h"
#include "widgets/myqmdiarea.h"

dlgMisiones::dlgMisiones(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgMisiones)
{
    ui->setupUi(this);
    mdiArea = MyQmdiArea::Instance(this);

    connect(ui->pbAnadirMisioneros, SIGNAL(clicked()), this, SLOT(anadirMisionero()));

    cargarModelo();

}

dlgMisiones::~dlgMisiones()
{
    delete ui;
}

void dlgMisiones::recibirMisionero()
{

}

void dlgMisiones::anadirMisionero()
{
    QModelIndex indice = m_misiones->index(ui->twMisiones->currentIndex().row(), 0);

    if (!indice.isValid())
        return;

    mision_escogida = m_misiones->data(indice, Qt::DisplayRole).toInt();

    dlgPersona = new dlgNuevaPersona(this);
    connect(dlgPersona, SIGNAL(personaIntroducida()), this, SLOT(recibirMisionero()));

    QMdiSubWindow *window = mdiArea->addSubWindow(dlgPersona);
    window->show();
}

void dlgMisiones::cargarModelo()
{
    m_misiones = new QSqlTableModel(this);
    m_misiones->setTable("filipinas.missions");
    m_misiones->setHeaderData(1, Qt::Horizontal, "Nombre");
    m_misiones->setHeaderData(2, Qt::Horizontal, "Latín");
    m_misiones->setHeaderData(3, Qt::Horizontal, "Otros nombres");
    m_misiones->setSort(1, Qt::AscendingOrder);
    m_misiones->select();

    ui->twMisiones->setModel(m_misiones);
    ui->twMisiones->setSortingEnabled(true);
    ui->twMisiones->resizeColumnsToContents();
    ui->twMisiones->resizeRowsToContents();
    ui->twMisiones->setAlternatingRowColors(true);
    ui->twMisiones->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twMisiones->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twMisiones->horizontalHeader()->setStretchLastSection(true);
    ui->twMisiones->hideColumn(0);

    // escogemos la primera línea...
    QModelIndex index = m_misiones->index(0,0);
    ui->twMisiones->setCurrentIndex(index);

}
