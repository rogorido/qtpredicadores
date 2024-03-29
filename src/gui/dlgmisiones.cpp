#include "dlgmisiones.h"

#include <QMdiSubWindow>
#include <QModelIndex>
#include <QSqlQuery>
#include <QSqlTableModel>

#include "dlgentradamisionero.h"
#include "src/widgets/fechasdelegate.h"
#include "src/widgets/myqmdiarea.h"
#include "ui_dlgmisiones.h"

dlgMisiones::dlgMisiones(QWidget *parent)
    : QWidget(parent), ui(new Ui::dlgMisiones)
{
  ui->setupUi(this);
  mdiArea = MyQmdiArea::Instance(this);

  connect(ui->pbAnadirMisioneros, SIGNAL(clicked()), this,
          SLOT(anadirMisionero()));
  ui->twMisiones->setItemDelegateForColumn(
      2, new FechasDelegate(FechasDelegate::TipoFecha::ONLY_YEAR, this));
  ui->twMisiones->setItemDelegateForColumn(
      3, new FechasDelegate(FechasDelegate::TipoFecha::ONLY_YEAR, this));

  cargarModelo();
}

dlgMisiones::~dlgMisiones() { delete ui; }

void dlgMisiones::anadirMisionero()
{
  QModelIndex indice =
      m_misiones->index(ui->twMisiones->currentIndex().row(), 0);

  if (!indice.isValid()) return;

  mision_escogida = m_misiones->data(indice, Qt::DisplayRole).toInt();

  dlgMisionero = new dlgEntradaMisionero(mision_escogida, this);

  QMdiSubWindow *window = mdiArea->addSubWindow(dlgMisionero);
  window->show();
}

void dlgMisiones::cargarModelo()
{
  m_misiones = new QSqlTableModel(this);
  m_misiones->setTable("filipinas.missions");
  m_misiones->setHeaderData(1, Qt::Horizontal, "Número");
  m_misiones->setHeaderData(2, Qt::Horizontal, "Fecha inicio");
  m_misiones->setHeaderData(3, Qt::Horizontal, "Fecha final");
  m_misiones->setSort(2, Qt::AscendingOrder);
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
  ui->twMisiones->hideColumn(4);
  ui->twMisiones->hideColumn(5);
  ui->twMisiones->hideColumn(6);
  ui->twMisiones->hideColumn(7);
  ui->twMisiones->hideColumn(8);

  // escogemos la primera línea...
  QModelIndex index = m_misiones->index(0, 0);
  ui->twMisiones->setCurrentIndex(index);
}
