#include "dlggestionobras.h"
#include "ui_dlggestionobras.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QMdiSubWindow>

#include "dlgnuevaobra.h"
#include "dlgseleccionargeneral.h"

#include "src/widgets/myqmdiarea.h"

#include "src/models/sqlfiltrogestor.h"
#include "src/models/qjsonmodel.h"
#include "src/models/obrasmodel.h"

const QString sql_general = "SELECT * FROM vistas.w_works_general";
const QString sql_con_reedicion = "SELECT DISTINCT work_id FROM works_details WHERE details @> '{\"tipo\":\"reedición\"}'";

const QString sql_estadisticas_reediciones = "SELECT work_id, title, autor, place_print_original, date_print, COUNT(*) AS total "
        "FROM w_works_general "
        "JOIN works_details wd USING(work_id) "
        "WHERE wd.details @> '{\"tipo\":\"reedición\"}' "
        "GROUP BY 1,2, 3, 4, 5 "
        "ORDER BY total DESC";

// no me acuerdo por qué hago esto así en lugar de contar las rows del modelo...
const QString sqlcontar = "SELECT count(*) FROM vistas.w_works_general";

dlgGestionObras::dlgGestionObras(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgGestionObras)
{
    ui->setupUi(this);
    mdiarea = MyQmdiArea::Instance(this);

    // no recuerdo por qué guardo esto en esta variable...
    sqlactivo_general = sql_general;
    sqlactivo_estadisticas = sql_estadisticas_reediciones;

    // ver en header: esto debería ser uno!
    obras_model = ObrasModel::InstanceModel();
    works_model = new QSqlQueryModel(this);
    works_statistics_model = new QSqlQueryModel(this);

    sql_gestor_general = new SqlFiltroGestor(sql_general, this);
    sql_gestor_estadisticas = new SqlFiltroGestor(sql_estadisticas_reediciones, this);

    json_detalles = new QJsonModel(this);

    cargarModelos();
    cargarMenus();

    connect(sql_gestor_general, SIGNAL(actualizadoSqlFiltroGestor(QString)), this, SLOT(actualizarSqlGeneral(QString)));
    connect(sql_gestor_general, SIGNAL(actualizadoSqlFiltroGestor(QString)), this, SLOT(actualizarSqlEstadisticas(QString)));
    connect(ui->tvObras->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            this, SLOT(seleccionarObra(QModelIndex)));
    connect(ui->tvObrasReediciones->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            this, SLOT(seleccionarObra(QModelIndex)));

    ui->tvObras->verticalHeader()->hide();
    ui->tvObras->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->tvObras, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(menuContextual(const QPoint &)));

}

dlgGestionObras::~dlgGestionObras()
{
    emit infoObraSeleccionadaBorrar();
    delete ui;
}

void dlgGestionObras::contarTotal()
{
    //total_filtrado = obispos_model->rowCount();
    total_filtrado = works_model->rowCount();

    emit infoBarra(total_filtrado);
}

void dlgGestionObras::on_rbManuscritos_clicked()
{
    sql_gestor_general->quitarFiltro("publicado");
    sql_gestor_general->anadirFiltro("manuscrito", "manuscrit = TRUE");
}

void dlgGestionObras::actualizarSqlGeneral(const QString s)
{
    sqlactivo_general = s;

    works_model->setQuery(sqlactivo_general);

    contarTotal();
}

void dlgGestionObras::actualizarSqlEstadisticas(const QString s)
{
    sqlactivo_estadisticas = s;
    works_statistics_model->setQuery(sqlactivo_estadisticas);

}

void dlgGestionObras::modificarObra()
{
    QModelIndex idx = ui->tvObras->currentIndex();

    if (!idx.isValid())
        return;

    int row = ui->tvObras->currentIndex().row();
    idx = works_model->index(row, 1);
    if (!idx.isValid())
        return;
    work_id = works_model->data(idx, Qt::DisplayRole).toInt();

    qDebug() << "la id es..." << work_id;

    dlgObraAModificar = new dlgNuevaObra(this, work_id);
    QMdiSubWindow *window = mdiarea->addSubWindow(dlgObraAModificar);
    connect(dlgObraAModificar, SIGNAL(introducidaObra()), this, SLOT(actualizarModeloTrasObraActualizada()));
    window->show();
}

void dlgGestionObras::verPersona()
{

}

void dlgGestionObras::modificarPersona()
{

}

void dlgGestionObras::actualizarModeloTrasObraActualizada()
{
    // esto es un slot que se activa cuando actualizamos una obra
    works_model->setQuery(sqlactivo_general);

    contarTotal();
}

void dlgGestionObras::seleccionarObra(const QModelIndex &idx)
{
    if (!idx.isValid())
        return;

    int row, id;
    QModelIndex indice;

    /*
     * Ahora el asunto depende de cuál es el tab que está seleccionado.
     */

    if (ui->tabWidget->currentIndex() == 0 ) {
        row = ui->tvObras->currentIndex().row();
        indice = works_model->index(row, 1);
        id = indice.data().toInt();
    }
    else {
        row = ui->tvObrasReediciones->currentIndex().row();
        indice = works_statistics_model->index(row, 0); // cuidado aquí work_id es 0
        id = indice.data().toInt();
    }

    QString mensaje = QString("Obra_id: ") + QString::number(id);
    emit infoObraSeleccionada(mensaje);

    mostrarDetalles(id);
    mostrarMaterias(id);

}

void dlgGestionObras::recibirTema(const Tema tema)
{
    elementopareado nuevotema;

    nuevotema.id = tema.getId();
    nuevotema.elemento = tema.getTema();

    materias_escogidas.append(nuevotema);
    QListWidgetItem *item = new QListWidgetItem(nuevotema.elemento, ui->lwTemas);
    Q_UNUSED(item)

    generarSQLMaterias();

}

void dlgGestionObras::recibirAutor(const Persona autor)
{
    elementopareado nuevoautor;

    nuevoautor.id = autor.getId();
    nuevoautor.elemento = autor.getNombreCompleto();

    autores_escogidos.append(nuevoautor);
    QListWidgetItem *item = new QListWidgetItem(nuevoautor.elemento, ui->lwAutores);
    Q_UNUSED(item)

    generarSQLAutores();

}

void dlgGestionObras::cargarMenus()
{
    menuContexto = new QMenu(this);

    a_verPersona = new QAction("Ver datos de persona", this);
    a_cambiarObra = new QAction("Modificar obra", this);
    a_cambiarPersona = new QAction("Modificar persona", this);

    connect(a_verPersona, SIGNAL(triggered(bool)), this, SLOT(verPersona()));
    connect(a_cambiarPersona, SIGNAL(triggered(bool)), this, SLOT(modificarPersona()));
    connect(a_cambiarObra, SIGNAL(triggered(bool)), this, SLOT(modificarObra()));

    menuContexto->addAction(a_verPersona);
    menuContexto->addAction(a_cambiarPersona);
    menuContexto->addAction(a_cambiarObra);
}

void dlgGestionObras::cargarModelos()
{
    works_model->setQuery(sqlactivo_general);
    ui->tvObras->setModel(works_model);

    ui->tvObras->setAlternatingRowColors(true);
    //ui->twResoluciones->setColumnWidth(1, 80);
    ui->tvObras->hideColumn(1);
    ui->tvObras->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvObras->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tvObras->setSortingEnabled(true);
    //works_model->sort(1, Qt::AscendingOrder);

    ui->tvObras->resizeColumnsToContents();
    ui->tvObras->resizeRowsToContents();
    ui->tvObras->horizontalHeader()->setStretchLastSection(true);
    ui->tvObras->setAutoScroll(false);
    //ui->tvObras->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    //ui->tvObras->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    // escogemos la primera línea del modelo...
    QModelIndex index = works_model->index(0,0);
    if (index.isValid()) {
        ui->tvObras->setCurrentIndex(index);
    }

    works_statistics_model->setQuery(sql_estadisticas_reediciones);
    ui->tvObrasReediciones->setModel(works_statistics_model);

    ui->tvObrasReediciones->setAlternatingRowColors(true);
    //ui->twResoluciones->setColumnWidth(1, 80);
    ui->tvObrasReediciones->hideColumn(0);
    ui->tvObrasReediciones->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvObrasReediciones->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tvObrasReediciones->setSortingEnabled(true);
    //works_model->sort(1, Qt::AscendingOrder);

    ui->tvObrasReediciones->resizeColumnsToContents();
    ui->tvObrasReediciones->resizeRowsToContents();
    ui->tvObrasReediciones->horizontalHeader()->setStretchLastSection(true);
    ui->tvObrasReediciones->setAutoScroll(false);
    //ui->tvObras->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    //ui->tvObras->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

}

void dlgGestionObras::generarSQLMaterias()
{
    QString sql;

    if (materias_escogidas.size() == 0) {
        sql_gestor_general->quitarFiltro("materias");
        return;
    }

    // construimos la SQL
    for (int var = 0; var < materias_escogidas.size(); ++var) {
        sql += QString("theme_id = ") + QString::number(materias_escogidas.at(var).id) + QString(" OR ");
    }
    // borramos el último OR
    sql.chop(4);
    sql = QString("work_id IN (SELECT DISTINCT work_id FROM works_themes WHERE ") + sql + QString(")");

    qDebug() << "el filtro es: " << sql;

    sql_gestor_general->anadirFiltro("materias", sql);

}

void dlgGestionObras::generarSQLAutores()
{
    QString sql;

    if (autores_escogidos.size() == 0) {
        sql_gestor_general->quitarFiltro("autores");
        return;
    }

    // construimos la SQL
    for (int var = 0; var < autores_escogidos.size(); ++var) {
        sql += QString("author_id = ") + QString::number(autores_escogidos.at(var).id) + QString(" OR ");
    }
    // borramos el último OR
    sql.chop(4);
    sql = QString("work_id IN (SELECT DISTINCT work_id FROM works WHERE ") + sql + QString(")");

    qDebug() << "el filtro es: " << sql;

    sql_gestor_general->anadirFiltro("autores", sql);

}

void dlgGestionObras::mostrarDetalles(const int obra_id)
{
    json_detalles = obras_model->devolverDetalles(obra_id);
    ui->twDetalles->setModel(json_detalles);
    ui->twDetalles->expandAll();
    ui->twDetalles->resizeColumnToContents(0);
    ui->twDetalles->resizeColumnToContents(1);
}

void dlgGestionObras::mostrarMaterias(const int obra_id)
{
    QSqlQuery query;
    QVector<int> temas;

    temas = obras_model->materiasObra(obra_id);

    // hay que borrar antes el widget porque sino lo añade todo...
    ui->lwMaterias->clear();

    for (int var = 0; var < temas.size(); ++var) {
        query.exec(QString("SELECT * FROM themes WHERE theme_id=%1").arg(temas.at(var)));
        query.first();
        /* añadimos un elem a la tabla */
        QListWidgetItem *item = new QListWidgetItem(query.value(1).toString(), ui->lwMaterias);

    }

}

void dlgGestionObras::on_rbImpresos_clicked()
{
    sql_gestor_general->quitarFiltro("manuscrito");
    sql_gestor_general->anadirFiltro("publicado", "printed = TRUE");
}

void dlgGestionObras::on_rbTodos_clicked()
{
    sql_gestor_general->quitarFiltro("manuscrito");
    sql_gestor_general->quitarFiltro("publicado");

}

void dlgGestionObras::on_ckSinMateria_stateChanged(int arg1)
{
    Q_UNUSED(arg1)

    if (ui->ckSinMateria->checkState() == Qt::Checked)
        sql_gestor_general->anadirFiltro("sinmaterias", "work_id NOT IN (SELECT DISTINCT work_id FROM works_themes)");
    else
        sql_gestor_general->quitarFiltro("sinmaterias");
}

void dlgGestionObras::menuContextual(const QPoint &point)
{
    menuContexto->popup(ui->tvObras->viewport()->mapToGlobal(point));
}

void dlgGestionObras::on_pbAnadirTema_clicked()
{
    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(TEMA, true, this);

    connect(dlgseleccionar, SIGNAL(temaEscogidoSignal(Tema)), this, SLOT(recibirTema(Tema)));
    QMdiSubWindow *window = mdiarea->addSubWindow(dlgseleccionar);
    window->show();

}

void dlgGestionObras::on_pbQuitarTema_clicked()
{

    QModelIndex idx = ui->lwTemas->currentIndex();

    if (!idx.isValid())
        return;

    QString valor = idx.data().toString();

    ui->lwTemas->takeItem(ui->lwTemas->currentRow());

    for (int i = 0; i < materias_escogidas.size(); ++i) {
      if(materias_escogidas.at(i).elemento == valor){
        materias_escogidas.removeAt(i);
        break;
      }
     }

    generarSQLMaterias();
}

void dlgGestionObras::on_pbQuitarTemasTodos_clicked()
{
    ui->lwTemas->clear();
    materias_escogidas.clear();
    generarSQLMaterias();
}

void dlgGestionObras::on_ckConReedicion_stateChanged(int arg1)
{
    Q_UNUSED(arg1)

    QString filtro;

    if (ui->ckConReedicion->checkState() == Qt::Checked) {
        filtro = QString("work_id IN (") + sql_con_reedicion + QString(")");
        sql_gestor_general->anadirFiltro("reedicion", filtro);
    }
    else
        sql_gestor_general->quitarFiltro("reedicion");

}

void dlgGestionObras::on_pbAnadirAutor_clicked()
{
    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(PERSONA, true, this);

    connect(dlgseleccionar, SIGNAL(personaEscogidaSignal(Persona)), this, SLOT(recibirAutor(Persona)));
    QMdiSubWindow *window = mdiarea->addSubWindow(dlgseleccionar);
    window->show();

}

void dlgGestionObras::on_pbQuitarAutor_clicked()
{
    QModelIndex idx = ui->lwAutores->currentIndex();

    if (!idx.isValid())
        return;

    QString valor = idx.data().toString();

    ui->lwAutores->takeItem(ui->lwTemas->currentRow());

    for (int i = 0; i < autores_escogidos.size(); ++i) {
      if(autores_escogidos.at(i).elemento == valor){
        autores_escogidos.removeAt(i);
        break;
      }
     }

    generarSQLAutores();
}

void dlgGestionObras::on_pbQuitarAutoresTodos_clicked()
{
    ui->lwAutores->clear();
    autores_escogidos.clear();
    generarSQLAutores();
}

void dlgGestionObras::on_pbResetearFiltros_clicked()
{
    /*
     * realmente esto así es un poco tosco...
     */

    ui->lwAutores->clear();
    autores_escogidos.clear();

    ui->lwTemas->clear();
    materias_escogidas.clear();

    ui->ckConReedicion->setCheckState(Qt::Unchecked);
    ui->ckSinMateria->setCheckState(Qt::Unchecked);

    ui->rbTodos->setChecked(true);

    sql_gestor_general->borrarFiltros();
}

void dlgGestionObras::on_btModificarObra_clicked()
{
    modificarObra();
}
