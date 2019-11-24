#include "dlggestionpersonas.h"

#include <QAction>
#include <QDebug>
#include <QMdiSubWindow>
#include <QMenu>
#include <QModelIndex>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include "dlgnuevapersona.h"
#include "src/models/personasmodel.h"
#include "src/models/qjsonmodel.h"
#include "src/models/sqlfiltrogestor.h"
#include "src/objs/proxynombres.h"
#include "src/widgets/fechasdelegate.h"
#include "src/widgets/myqmdiarea.h"
#include "ui_dlggestionpersonas.h"

const QString sql_general = "SELECT * FROM vistas.persons_alternatives";

// no me acuerdo por qué hago esto así en lugar de contar las rows del modelo...
const QString sqlcontar = "SELECT count(*) FROM vistas.persons_alternatives";

const QString sql_obispos =
    "SELECT DISTINCT bishop_person_id FROM bishops.bishops";
const QString sql_autores = "SELECT DISTINCT author_id FROM works.works";

dlgGestionPersonas::dlgGestionPersonas(QWidget *parent)
    : QWidget(parent), ui(new Ui::dlgGestionPersonas)
{
  ui->setupUi(this);
  mdiarea = MyQmdiArea::Instance(this);

  // no recuerdo por qué guardo esto en esta variable...
  sqlactivo = sql_general;

  m_persons = PersonasModel::InstanceModel();

  sql_gestor = new SqlFiltroGestor(sql_general, this);
  connect(sql_gestor, SIGNAL(actualizadoSqlFiltroGestor(QString)), this,
          SLOT(actualizarSql(QString)));

  json_detalles = new QJsonModel(this);
  m_works = new QSqlQueryModel(this);
  ui->twObras->setModel(m_works);
  m_obispados = new QSqlQueryModel(this);
  ui->twObispos->setModel(m_obispados);
  ui->twObispos->setItemDelegateForColumn(
      1, new FechasDelegate(FechasDelegate::TipoFecha::ONLY_YEAR, this));
  ui->twObispos->setItemDelegateForColumn(
      2, new FechasDelegate(FechasDelegate::TipoFecha::ONLY_YEAR, this));

  cargarModelos();
  cargarMenus();

  ui->tvPersonas->setContextMenuPolicy(Qt::CustomContextMenu);

  connect(ui->tvPersonas, SIGNAL(customContextMenuRequested(const QPoint &)),
          this, SLOT(menuContextual(const QPoint &)));
  connect(ui->tvPersonas->selectionModel(),
          SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this,
          SLOT(seleccionarPersona(QModelIndex)));

  connect(ui->txtFiltro, SIGNAL(textEdited(QString)), this,
          SLOT(actualizarFiltro(QString)));
}

dlgGestionPersonas::~dlgGestionPersonas()
{
  emit infoPersonaSeleccionadaBorrar();
  delete ui;
}

void dlgGestionPersonas::contarTotal()
{
  // total_filtrado = obispos_model->rowCount();
  total_filtrado = m_persons->rowCount();

  emit infoBarra(total_filtrado);
}

void dlgGestionPersonas::menuContextual(const QPoint &point)
{
  menuContexto->popup(ui->tvPersonas->viewport()->mapToGlobal(point));
}

void dlgGestionPersonas::actualizarFiltro(const QString filtro)
{
  if (filtro.length() > 2) {
    proxy_personas->setFilterRegExp(
        QRegExp(filtro, Qt::CaseInsensitive, QRegExp::FixedString));
    ui->tvPersonas->resizeRowsToContents();
    ui->tvPersonas->resizeColumnsToContents();
    contarTotal();
  }
  else {
    proxy_personas->setFilterRegExp(
        QRegExp("", Qt::CaseInsensitive, QRegExp::FixedString));
    ui->tvPersonas->resizeRowsToContents();
    ui->tvPersonas->resizeColumnsToContents();
    contarTotal();
  }
}

void dlgGestionPersonas::actualizarSql(const QString s)
{
  sqlactivo = s;

  m_persons->setQuery(sqlactivo);
  ui->tvPersonas->resizeColumnsToContents();
  ui->tvPersonas->resizeRowsToContents();

  contarTotal();
}

void dlgGestionPersonas::modificarPersona()
{
  QModelIndex indice =
      proxy_personas->index(ui->tvPersonas->currentIndex().row(), 0);
  if (!indice.isValid()) return;

  int id = m_persons->data(proxy_personas->mapToSource(indice), Qt::DisplayRole)
               .toInt();
  // qDebug() << "escogido: " << id;

  dlgPersonaAModificar = new dlgNuevaPersona(this, id);
  QMdiSubWindow *window = mdiarea->addSubWindow(dlgPersonaAModificar);
  connect(dlgPersonaAModificar, SIGNAL(personaIntroducida()), this,
          SLOT(actualizarModeloTrasPersonaActualizada()));
  window->show();
}

void dlgGestionPersonas::actualizarModeloTrasPersonaActualizada()
{
  m_persons->setQuery(sqlactivo);
  contarTotal();
}

void dlgGestionPersonas::seleccionarPersona(const QModelIndex &idx)
{
  Q_UNUSED(idx)
  // NOTE: aquí no estoy usando lo de idx... he cogido este código de lo de
  // modificar persona...
  QModelIndex indice =
      proxy_personas->index(ui->tvPersonas->currentIndex().row(), 0);
  if (!indice.isValid()) return;

  int id = m_persons->data(proxy_personas->mapToSource(indice), Qt::DisplayRole)
               .toInt();
  // qDebug() << "escogido: " << id;

  QString mensaje = QString("Persona_id: ") + QString::number(id);
  emit infoPersonaSeleccionada(mensaje);

  json_detalles = m_persons->devolverDetalles(id);

  /*
   * me sorprende que haya que hacer un setModel() cada vez que cambia esto
   * pero si lo pongo en el constructor del Form el asunto no funciona...
   */
  ui->twDetalles->setModel(json_detalles);
  ui->twDetalles->expandAll();
  ui->twDetalles->resizeColumnToContents(0);
  ui->twDetalles->resizeColumnToContents(1);

  actualizarObras(id);
  actualizarObispados(id);
}

void dlgGestionPersonas::cargarMenus()
{
  menuContexto = new QMenu(this);

  a_cambiarPersona = new QAction("Modificar persona", this);
  connect(a_cambiarPersona, SIGNAL(triggered(bool)), this,
          SLOT(modificarPersona()));
  menuContexto->addAction(a_cambiarPersona);
}

void dlgGestionPersonas::cargarModelos()
{
  m_persons->setQuery(sqlactivo);

  proxy_personas = new ProxyNombres(PERSONASGESTION, this);
  proxy_personas->setSourceModel(m_persons);

  proxy_personas->setHeaderData(1, Qt::Horizontal, "Nombre");
  proxy_personas->setHeaderData(2, Qt::Horizontal, "Apellidos");
  proxy_personas->setHeaderData(3, Qt::Horizontal, "Origen");
  proxy_personas->setHeaderData(5, Qt::Horizontal, "Nacimiento");
  proxy_personas->setHeaderData(6, Qt::Horizontal, "Muerte");
  proxy_personas->setHeaderData(7, Qt::Horizontal, "Tipo");

  ui->tvPersonas->setModel(proxy_personas);

  ui->tvPersonas->setAlternatingRowColors(true);
  // ui->twResoluciones->setColumnWidth(1, 80);

  ui->tvPersonas->hideColumn(0);
  ui->tvPersonas->hideColumn(4);  // esto es lo de male
  // las de los idiomas
  ui->tvPersonas->hideColumn(8);
  ui->tvPersonas->hideColumn(9);
  ui->tvPersonas->hideColumn(10);
  ui->tvPersonas->hideColumn(11);
  ui->tvPersonas->hideColumn(12);

  ui->tvPersonas->horizontalHeader()->setStretchLastSection(true);
  ui->tvPersonas->setSortingEnabled(true);
  ui->tvPersonas->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tvPersonas->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->tvPersonas->verticalHeader()->hide();

  proxy_personas->sort(1, Qt::AscendingOrder);

  ui->tvPersonas->resizeColumnsToContents();
  ui->tvPersonas->resizeRowsToContents();

  // escogemos la primera línea del modelo...
  QModelIndex index = proxy_personas->index(0, 0);
  if (index.isValid()) {
    ui->tvPersonas->setCurrentIndex(index);
  }
}

void dlgGestionPersonas::actualizarObras(const int id)
{
  QString sql;

  sql = QString("SELECT title, language_work FROM works WHERE author_id = %1")
            .arg(id);
  m_works->setQuery(sql);
  ui->twObras->horizontalHeader()->setStretchLastSection(true);
  ui->twObras->setSortingEnabled(true);
  ui->twObras->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->twObras->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->twObras->resizeColumnToContents(0);
  ui->twObras->resizeRowsToContents();
}

void dlgGestionPersonas::actualizarObispados(const int id)
{
  QString sql;

  sql = QString(
            "SELECT d.diocese_name, b.date_nomination, b.date_end "
            "FROM bishops.bishops b "
            "JOIN dioceses d USING(diocese_id) "
            "WHERE bishop_person_id = %1")
            .arg(id);
  m_obispados->setQuery(sql);
  // ui->twObispos->horizontalHeader()->setStretchLastSection(true);
  ui->twObispos->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->twObispos->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->twObispos->resizeColumnToContents(0);
  ui->twObispos->resizeRowsToContents();
}

void dlgGestionPersonas::on_ckObispos_stateChanged(int arg1)
{
  Q_UNUSED(arg1)

  QString filtro;

  if (ui->ckObispos->checkState() == Qt::Checked) {
    filtro = QString("person_id IN (") + sql_obispos + QString(")");
    sql_gestor->anadirFiltro("obispos", filtro);
  }
  else
    sql_gestor->quitarFiltro("obispos");
}

void dlgGestionPersonas::on_ckAutores_stateChanged(int arg1)
{
  Q_UNUSED(arg1)

  QString filtro;

  if (ui->ckAutores->checkState() == Qt::Checked) {
    filtro = QString("person_id IN (") + sql_autores + QString(")");
    sql_gestor->anadirFiltro("autores", filtro);
  }
  else
    sql_gestor->quitarFiltro("autores");
}

void dlgGestionPersonas::on_btModificarPersona_clicked() { modificarPersona(); }

void dlgGestionPersonas::on_btResetearFiltros_clicked()
{
  ui->ckAutores->setCheckState(Qt::Unchecked);
  ui->ckObispos->setCheckState(Qt::Unchecked);

  sql_gestor->borrarFiltros();
}
