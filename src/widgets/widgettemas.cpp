#include "widgettemas.h"

#include <QDebug>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QSqlQuery>
#include <QTableView>

#include "src/models/temasmodel.h"
#include "ui_widgettemas.h"

WidgetTemas::WidgetTemas(QWidget *parent)
    : QWidget(parent), ui(new Ui::WidgetTemas)
{
  ui->setupUi(this);

  m_temas = TemasModel::InstanceModel();
  m_temas->sort(1, Qt::AscendingOrder);

  /*
   * lo deshabilitamos por el puto error ese que da.
   * Mirar abajo...
   */
  ui->btQuitar->setEnabled(false);

  cargarModelos();
}

WidgetTemas::~WidgetTemas() { delete ui; }

void WidgetTemas::on_btAnadir_clicked()
{
  bool valor;
  QModelIndex idx = temas_noseleccionados_proxy->index(
      ui->twNoSeleccionado->currentIndex().row(), 3);

  if (!idx.isValid()) return;

  valor =
      m_temas
          ->data(temas_noseleccionados_proxy->mapToSource(idx), Qt::DisplayRole)
          .toBool();
  valor = !valor;
  m_temas->setData(temas_noseleccionados_proxy->mapToSource(idx), valor,
                   Qt::EditRole);

  ui->twSeleccionado->resizeColumnsToContents();
  ui->twSeleccionado->resizeRowsToContents();

  crearSqlFiltro();
}

void WidgetTemas::on_btQuitar_clicked()
{
  /*
   * FIXME: por alguna misteriosa razón este código
   * que es exactamente el mismo que el del método anterior
   * provoca un crash. Creo que es un error de Qt...
   */
  bool valor;
  QModelIndex idx = temas_seleccionados_proxy->index(
      ui->twSeleccionado->currentIndex().row(), 3);

  if (!idx.isValid()) return;

  valor =
      m_temas
          ->data(temas_seleccionados_proxy->mapToSource(idx), Qt::DisplayRole)
          .toBool();
  qDebug() << "el valor es: " << valor;
  valor = !valor;
  m_temas->setData(temas_seleccionados_proxy->mapToSource(idx), valor,
                   Qt::EditRole);

  crearSqlFiltro();
}

void WidgetTemas::on_btQuitarTodos_clicked()
{
  QSqlQuery query;

  query.exec("UPDATE themes SET selected='f'");

  m_temas->select();
  ui->twNoSeleccionado->resizeColumnsToContents();
  ui->twNoSeleccionado->resizeRowsToContents();

  crearSqlFiltro();
}

void WidgetTemas::cargarModelos()
{
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
  ui->twNoSeleccionado->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->twNoSeleccionado->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->twSeleccionado->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->twSeleccionado->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->twNoSeleccionado->horizontalHeader()->setStretchLastSection(true);
  ui->twSeleccionado->horizontalHeader()->setStretchLastSection(true);

  connect(ui->twNoSeleccionado, SIGNAL(doubleClicked(QModelIndex)), this,
          SLOT(on_btAnadir_clicked()));
}

void WidgetTemas::crearSqlFiltro()
{
  QSqlQuery query;
  QList<int> lista_temas;

  query.exec("SELECT theme_id FROM themes WHERE selected='t'");

  while (query.next()) {
    lista_temas << query.value(0).toInt();
  }

  emit(temasSeleccionadosCambio(lista_temas));
}
