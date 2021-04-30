#include "dlgresoluciones.h"

#include <QDataWidgetMapper>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>

#include "dlgdetalles.h"
#include "dlgnuevaresolucion.h"
#include "dlgseleccionargeneral.h"
#include "src/models/qjsonmodel.h"
#include "src/models/sqlfiltrogestor.h"
#include "src/widgets/myqmdiarea.h"
#include "ui_dlgresoluciones.h"

const QString sql_general =
    "SELECT DISTINCT ON (r.resolution_id) * FROM resolutions r "
    "LEFT JOIN resolutions_details rd ON r.resolution_id = rd.resolution_id "
    "LEFT JOIN chapters c ON r.chapter = c.chapter_id";

dlgResoluciones::dlgResoluciones(QWidget *parent)
    : QWidget(parent), ui(new Ui::dlgResoluciones)
{
  ui->setupUi(this);

  mdiarea = MyQmdiArea::Instance(this);

  json_model = new QJsonModel(this);
  ui->twDetalles->setModel(json_model);

  json_anadir_model = new QJsonModel(this);

  sql_gestor = new SqlFiltroGestor(sql_general, this);
  connect(sql_gestor, SIGNAL(actualizadoSqlFiltroGestor(QString)), this,
          SLOT(actualizarSql(QString)));

  cargarModelos();
  cargarTablasTemporales();
  cargarMapper();
  cargarInfos();

  connect(ui->twResoluciones->selectionModel(),
          SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this,
          SLOT(seleccionarResolucion(QModelIndex)));
  connect(ui->wdTemas, SIGNAL(temasSeleccionadosCambio(QList<int>)), this,
          SLOT(temasSeleccionadosCambiados(QList<int>)));
  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(aplicarFiltro()));

  // deshabilitamos este botón por un puto error que da (ver abajo)
  ui->btDeSeleccionarEpigrafe->setEnabled(false);
}

dlgResoluciones::~dlgResoluciones()
{
  // borramos la tabla temporal
  QSqlQuery query;
  query.exec("DROP TABLE temp_epigrafes");

  delete ui;
}

void dlgResoluciones::seleccionarResolucion(const QModelIndex &idx)
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
  if (!indice.isValid()) return;

  resolucion_id = resoluciones_model->data(indice, Qt::DisplayRole).toInt();
  temas_model->setFilter(QString("resolution_id=%1").arg(resolucion_id));

  cargarDetalles(resolucion_id);
}

void dlgResoluciones::recibirNuevoTema(Tema t)
{
  int tema_id = t.getId();

  QSqlQuery query;
  query.prepare(
      "INSERT INTO resolutions_themes(theme_id, resolution_id) VALUES(:tema, "
      ":resolucion)");
  query.bindValue(":tema", tema_id);
  query.bindValue(":resolucion", resolucion_id);
  query.exec();

  temas_model->select();
  temas_model->setFilter(QString("resolution_id=%1").arg(resolucion_id));
}

void dlgResoluciones::recibirNuevoJsonDetalles()
{
  QSqlQuery query;
  int totaljson = json_anadir_model->getSize();

  if (totaljson == 0) return;

  qDebug() << "la resulu-id es: " << resolucion_id;

  for (int var = 0; var < totaljson; ++var) {
    QString jsonfinal = json_anadir_model->getJsonString(var);

    query.prepare(
        "INSERT INTO resolutions_details(resolution_id, details) "
        "VALUES(:resolucionid, :json)");
    query.bindValue(":resolucionid", resolucion_id);
    query.bindValue(":json", jsonfinal);
    query.exec();

    /*
     * y ahora actualizamos el modelo de la view
     */
    QJsonObject json_temporal = json_anadir_model->getJsonObject(var);
    json_model->anadirJson(json_temporal);
  }

  json_model->resetearModelo();

  // borramos el contenido json_anadir_model...
  json_anadir_model->clear();

  /*
   * NOTE: esto es un poco cutre, pero volver a cargar los detalles
   * pq así se vuelve a llenar la lista de ids_details pq si no,
   * puede estar vacía... Realmente habría que hacer aquí algún sistema
   * para coger lo que se haya metido pero da igual...
   */
  cargarDetalles(resolucion_id);
}

void dlgResoluciones::cargarDetalles(int id)
{
  QSqlQuery query;
  QString sql;
  QJsonDocument json;

  sqlactivo = sql_general;

  sql = QString(
            "SELECT detail_id, details FROM resolutions_details WHERE "
            "resolution_id=%1")
            .arg(id);
  query.exec(sql);

  // borramos lo que ya está
  json_model->clear();
  ids_resolutions_details.clear();

  /*
   * joder, que lío hay que hacer para construir un json...
   * hay que usar eso de QByteArray pq con una QString normal
   * no hay manera...
   */
  while (query.next()) {
    int id = query.value(0).toInt();
    QByteArray datos = query.value(1).toByteArray();
    json = QJsonDocument::fromJson(datos);
    /*
     * tenemos que pasar json.object que construye un
     * QjsonObject, que es al parecer tb un QJsonValue
     * y es lo que pide anadirJson...
     */
    json_model->anadirJson(json.object());

    ids_resolutions_details << id;
  }

  json_model->resetearModelo();

  json_model->setIdDetails(ids_resolutions_details);
}

void dlgResoluciones::aplicarFiltro()
{
  resoluciones_model->setQuery(
      sql_general + QString(" WHERE details ?| array['mandato', 'prohibición',"
                            " 'comisión', 'admonición'];"));
}

void dlgResoluciones::actualizarSql(QString s)
{
  sqlactivo = s;

  resoluciones_model->setQuery(sqlactivo);
}

void dlgResoluciones::temasSeleccionadosCambiados(QList<int> lista_temas)
{
  QSqlQuery query;
  QString sql_temas, sql_temp, sql_final;

  if (lista_temas.size() == 0) {
    sql_gestor->quitarFiltro("temas");
    return;
  }

  for (int var = 0; var < lista_temas.size(); ++var) {
    sql_temas += QString::number(lista_temas.at(var)) + QString(",");
  }

  // quitamos la última coma y ponemos el resto
  sql_temas.chop(1);
  sql_temas = QString(
                  "SELECT DISTINCT resolution_id FROM resolutions_themes WHERE "
                  "theme_id IN (") +
              sql_temas + QString(")");
  query.exec(sql_temas);

  while (query.next()) {
    sql_temp += QString::number(query.value(0).toInt()) + QString(",");
  }

  // quitamos la última coma y ponemos el resto
  sql_temp.chop(1);
  // tenemos que poner lo de r.resolution por la abfrage subyacente que tiene un
  // alias
  sql_final = QString("r.resolution_id IN (") + sql_temp + QString(")");

  sql_gestor->anadirFiltro("temas", sql_final);
}

void dlgResoluciones::on_btAnadirTema_clicked()
{
  dlgseleccionar = new dlgSeleccionarGeneral(TEMA, true, this);
  connect(dlgseleccionar, SIGNAL(temaEscogidoSignal(Tema)), this,
          SLOT(recibirNuevoTema(Tema)));

  QMdiSubWindow *window = mdiarea->addSubWindow(dlgseleccionar);
  window->show();
}

void dlgResoluciones::on_btQuitarTema_clicked()
{
  /*
   * sigo sin entender cómo coño es tan difícil esto de
   * extraer el valor de una tabla, del modelo subyacente, etc.
   */
  int row = ui->twTemas->currentIndex().row();
  QModelIndex idx = temas_model->index(row, 0);  // columna 0, pq está el id

  if (!idx.isValid()) return;

  int valor = temas_model->data(idx, Qt::DisplayRole).toInt();

  QSqlQuery query;
  query.prepare(
      "DELETE FROM resolutions_themes WHERE resolutions_themes_id=:valor");
  query.bindValue(":valor", valor);
  query.exec();

  temas_model->select();
  temas_model->setFilter(QString("resolution_id=%1").arg(resolucion_id));
}

void dlgResoluciones::on_btAnadirDetalles_clicked()
{
  dlgDetalles *dlgdetalles =
      new dlgDetalles(json_anadir_model, RESOLUCION, true, this);
  connect(dlgdetalles, SIGNAL(accepted()), this,
          SLOT(recibirNuevoJsonDetalles()));

  QMdiSubWindow *window = mdiarea->addSubWindow(dlgdetalles);
  window->show();
}

void dlgResoluciones::on_btBorrarDetalles_clicked()
{
  /*
   * la idea es la siguiente: cogemos el índice; si no es válido
   * salimos sin más. Si es válido continúa y coge el del padre.
   * Y aquí está el truco: si el índice del padre no es válido, eso
   * quiere decir que estamos ya en el nivel superior y por tanto
   * el índice que nos interesa es idx, pero si es válido, lo que
   * nos interesa es el índice padre.
   *
   * NOTE: esto evidentemente sólo sirve cuando hay solo un subnivel,
   * si hubiera más subniveles no funcionaría!
   */
  QSqlQuery query;
  QModelIndex idx = ui->twDetalles->currentIndex();
  int ordinal;

  if (!idx.isValid()) return;

  QModelIndex padre = idx.parent();

  if (!padre.isValid())
    ordinal = idx.row();
  else
    ordinal = padre.row();

  /*
   * ahora necesitamos sacar el detail_id de la
   * lista para hacer una query DELETE.
   * tenemos que usar takeAt para eleminar ese elemetno de
   * la lista ids_resolutions_details
   */
  qDebug() << "tamaño de la lista de ids: " << ids_resolutions_details.size();
  int id_detail = ids_resolutions_details.takeAt(ordinal);
  QMessageBox::StandardButton reply;
  reply =
      QMessageBox::question(this, "Borrar detalles de resolución",
                            "¿Seguro que quieres borrar este bloque de datos?",
                            QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    query.exec(QString("DELETE FROM resolutions_details WHERE detail_id=%1")
                   .arg(id_detail));
    json_model->borrarJson(ordinal);
  }
}

void dlgResoluciones::on_btSeleccionarEpigrafe_clicked()
{
  /*
   * para esta cosa tan rara mirar esto:
   * https://forum.qt.io/topic/6401/solved-check-if-a-line-is-selected-from-a-qtableview/13
   */
  if (!ui->twEpigrafesTodos->selectionModel()->isSelected(
          ui->twEpigrafesTodos->currentIndex()))
    return;

  bool valor;
  QModelIndex idx = epigrafes_noseleccionados_proxy->index(
      ui->twEpigrafesTodos->currentIndex().row(), 1);

  if (!idx.isValid()) return;

  valor = m_epigrafes
              ->data(epigrafes_noseleccionados_proxy->mapToSource(idx),
                     Qt::DisplayRole)
              .toBool();
  valor = !valor;
  m_epigrafes->setData(epigrafes_noseleccionados_proxy->mapToSource(idx), valor,
                       Qt::EditRole);

  ui->twEpigrafesSeleccionados->resizeColumnsToContents();
  ui->twEpigrafesSeleccionados->resizeRowsToContents();

  crearFiltroEpigrafes();
}

void dlgResoluciones::on_btDeSeleccionarEpigrafe_clicked()
{
  /*
   * FIXME: por alguna misteriosa razón este código
   * que es exactamente el mismo que el del método anterior
   * provoca un crash. Creo que es un error de Qt...
   */
  if (!ui->twEpigrafesSeleccionados->selectionModel()->isSelected(
          ui->twEpigrafesSeleccionados->currentIndex()))
    return;

  bool valor;
  QModelIndex idx = epigrafes_seleccionados_proxy->index(
      ui->twEpigrafesSeleccionados->currentIndex().row(), 1);

  if (!idx.isValid()) return;

  valor = m_epigrafes
              ->data(epigrafes_seleccionados_proxy->mapToSource(idx),
                     Qt::DisplayRole)
              .toBool();
  qDebug() << "el valor es: " << valor;
  valor = !valor;
  m_epigrafes->setData(epigrafes_seleccionados_proxy->mapToSource(idx), valor,
                       Qt::EditRole);

  ui->twEpigrafesSeleccionados->resizeColumnsToContents();
  ui->twEpigrafesSeleccionados->resizeRowsToContents();
}

void dlgResoluciones::on_btDeseleccionarTodosEpigrafes_clicked()
{
  QSqlQuery query;

  query.exec("UPDATE temp_epigrafes SET selected = false");
  m_epigrafes->select();
  ui->twEpigrafesTodos->resizeColumnsToContents();
  ui->twEpigrafesTodos->resizeRowsToContents();

  sql_gestor->quitarFiltro("epigrafes");
}

void dlgResoluciones::cargarModelos()
{
  resoluciones_model = new QSqlQueryModel(this);
  resoluciones_model->setQuery(sql_general);
  resoluciones_model->setHeaderData(1, Qt::Horizontal, "Texto resolución");
  resoluciones_model->setHeaderData(2, Qt::Horizontal, "Capítulo");
  resoluciones_model->setHeaderData(3, Qt::Horizontal, "Epígrafe");
  ui->twResoluciones->setModel(resoluciones_model);
  ui->twResoluciones->hideColumn(0);
  ui->twResoluciones->setAlternatingRowColors(true);
  ui->twResoluciones->setColumnWidth(1, 80);
  // ui->twResoluciones->resizeColumnsToContents();
  // ui->twResoluciones->resizeRowsToContents();
  ui->twResoluciones->horizontalHeader()->setStretchLastSection(true);
  ui->twResoluciones->setSortingEnabled(true);
  ui->twResoluciones->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->twResoluciones->setSelectionMode(QAbstractItemView::SingleSelection);

  // escogemos la primera línea del modelo...
  QModelIndex index = resoluciones_model->index(0, 0);
  if (index.isValid()) {
    ui->twResoluciones->setCurrentIndex(index);
  }

  temas_model = new QSqlRelationalTableModel(this);
  temas_model->setTable("chapters.resolutions_themes");
  temas_model->setRelation(1,
                           QSqlRelation("general.themes", "theme_id", "theme"));
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

void dlgResoluciones::cargarTablasTemporales()
{
  /*
   * Esto realmente podría ir con lo de los modelos, pero lo pongo aquí.
   * El asunto es que creo una tabla temporal con los epígrafes y
   * lo uso para gestiones los epígrafes que se escogen, etc.
   */

  QSqlQuery query;

  query.exec(
      "CREATE TEMPORARY TABLE temp_epigrafes(epigrafe varchar(200), selected "
      "bool DEFAULT false)");
  query.exec(
      "INSERT INTO temp_epigrafes(epigrafe) SELECT DISTINCT small_title FROM "
      "resolutions ORDER BY small_title");

  m_epigrafes = new QSqlTableModel(this);
  m_epigrafes->setTable("temp_epigrafes");
  m_epigrafes->select();

  epigrafes_noseleccionados_proxy = new QSortFilterProxyModel(this);
  epigrafes_noseleccionados_proxy->setSourceModel(m_epigrafes);
  epigrafes_noseleccionados_proxy->setFilterFixedString("f");
  epigrafes_noseleccionados_proxy->setFilterKeyColumn(1);

  epigrafes_seleccionados_proxy = new QSortFilterProxyModel(this);
  epigrafes_seleccionados_proxy->setSourceModel(m_epigrafes);
  epigrafes_seleccionados_proxy->setFilterFixedString("t");
  epigrafes_seleccionados_proxy->setFilterKeyColumn(1);

  ui->twEpigrafesTodos->setModel(epigrafes_noseleccionados_proxy);
  ui->twEpigrafesSeleccionados->setModel(epigrafes_seleccionados_proxy);

  ui->twEpigrafesTodos->hideColumn(1);
  ui->twEpigrafesTodos->setAlternatingRowColors(true);
  // ui->twResoluciones->setColumnWidth(0, 80);
  ui->twEpigrafesTodos->resizeColumnsToContents();
  ui->twEpigrafesTodos->resizeRowsToContents();
  ui->twEpigrafesTodos->horizontalHeader()->setStretchLastSection(true);
  // ui->twEpigrafesTodos->setSortingEnabled(true);
  ui->twEpigrafesTodos->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->twEpigrafesTodos->setSelectionMode(QAbstractItemView::SingleSelection);

  ui->twEpigrafesSeleccionados->hideColumn(1);
  ui->twEpigrafesSeleccionados->setAlternatingRowColors(true);
  // ui->twResoluciones->setColumnWidth(0, 80);
  ui->twEpigrafesSeleccionados->resizeColumnsToContents();
  ui->twEpigrafesSeleccionados->resizeRowsToContents();
  ui->twEpigrafesSeleccionados->horizontalHeader()->setStretchLastSection(true);
  // ui->twEpigrafesSeleccionados->setSortingEnabled(true);
  ui->twEpigrafesSeleccionados->setSelectionBehavior(
      QAbstractItemView::SelectRows);
  ui->twEpigrafesSeleccionados->setSelectionMode(
      QAbstractItemView::SingleSelection);
}

void dlgResoluciones::cargarMapper()
{
  mapper_data = new QDataWidgetMapper(this);
  mapper_data->setModel(resoluciones_model);
  mapper_data->addMapping(ui->txtResolucion, 1);
  mapper_data->addMapping(ui->txtResolucionResumen, 3);
}

void dlgResoluciones::cargarInfos()
{
  ui->lblTotalResoluciones->setText(
      QString("Resoluciones: %1").arg(resoluciones_model->rowCount()));
}

void dlgResoluciones::crearFiltroEpigrafes()
{
  QSqlQuery query;
  QString sql_temp;
  QString sql_final;

  query.exec("SELECT * FROM temp_epigrafes WHERE selected = true");

  while (query.next()) {
    QString epigrafe = query.value(0).toString();
    sql_temp += " OR small_title = '" + epigrafe + "'";
  }

  // borramos el primer OR
  sql_temp = sql_temp.remove(0, 4);
  sql_final = QString("(") + sql_temp + QString(")");

  sql_gestor->anadirFiltro("epigrafes", sql_final);
}

void dlgResoluciones::on_btActualizarResolucion_clicked()
{
  dlgresolucion = new dlgNuevaResolucion(resolucion_id, 0, this);

  QMdiSubWindow *window = mdiarea->addSubWindow(dlgresolucion);
  window->show();
}
