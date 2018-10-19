#include "dlgdiocesis.h"
#include "ui_dlgdiocesis.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QSqlError>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QMdiSubWindow>

#include "src/models/sqlfiltrogestor.h"
#include "src/objs/proxynombres.h"
#include "dlgnuevadiocesis.h"
#include "dlgdiocesisdetalles.h"
#include "src/widgets/myqmdiarea.h"

const QString sql_general = "SELECT * from vistas.diocesis_general";
const QString sql_comprobar = "check_allbishops = false";
const QString sql_obispos = "SELECT * from vistas.obispos_general";
const QString sql_sinhierarchy = "url_hierarchy is NULL";

dlgDiocesis::dlgDiocesis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgDiocesis)
{
    ui->setupUi(this);
    mdiarea = MyQmdiArea::Instance(this);

    ui->twDiocesis->setContextMenuPolicy(Qt::CustomContextMenu);

    m_diocesis = new QSqlQueryModel(this);
    proxy_diocesis = new ProxyNombres(DIOCESIS, this);

    m_obispos = new QSqlQueryModel(this);
    m_obispos->setQuery(sql_obispos);
    m_obispos_proxy = new QSortFilterProxyModel(this);
    m_obispos_proxy->setSourceModel(m_obispos);

    sqlactivo = sql_general;
    sql_gestor = new SqlFiltroGestor(sql_general, this);
    connect(sql_gestor, SIGNAL(actualizadoSqlFiltroGestor(QString)), this, SLOT(actualizarSql(QString)));

    cargarModelos();
    cargarMenus();

    connect(ui->pbCerrar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    //connect(ui->twDiocesis->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
     //       this, SLOT(seleccionarDiocesis(QModelIndex)));
    connect(ui->twDiocesis, SIGNAL(clicked(const QModelIndex &)), this, SLOT(seleccionarDiocesis(QModelIndex)));
    connect(ui->txtFiltro, SIGNAL(textEdited(QString)), this, SLOT(actualizarFiltro(QString)));
    connect(ui->pbAbrirUrl, SIGNAL(clicked()), this, SLOT(abrirUrl()));
    connect(ui->twDiocesis, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(menuContextualDiocesis(QPoint)));
    connect(ui->btAnadirDetalles, SIGNAL(clicked()), this, SLOT(anadirDetallesDiocesis()));
    connect(ui->btModificarDiocesis, SIGNAL(clicked()), this, SLOT(modificarDiocesis()));

}

dlgDiocesis::~dlgDiocesis()
{
    delete ui;
}

void dlgDiocesis::seleccionarDiocesis(const QModelIndex &idx)
{
    /*
     * sacamos el índice de la columna 0 que es donde está
     * la id de la resolución, para luego convertirla en int
     * y usarla en el filtro del otro modelo.
     */
    QModelIndex indice = idx.model()->index(idx.row(), 0);
    if (!indice.isValid())
        return;

    QModelIndex indice_verdadero = proxy_diocesis->mapToSource(indice);

    if (!indice_verdadero.isValid())
        return;

    diocesis_seleccionada = m_diocesis->data(indice_verdadero, Qt::DisplayRole).toInt();

    mostrarObispos();
}

void dlgDiocesis::actualizarSql(QString s)
{
    sqlactivo = s;
    m_diocesis->setQuery(sqlactivo);
}

void dlgDiocesis::actualizarFiltro(const QString filtro)
{
    if (filtro.length() > 2) {
        proxy_diocesis->setFilterRegExp(QRegExp(filtro, Qt::CaseInsensitive, QRegExp::FixedString));
        ui->twDiocesis->resizeRowsToContents();
        ui->twDiocesis->resizeColumnsToContents();
    }
    else
    {
        proxy_diocesis->setFilterRegExp(QRegExp("", Qt::CaseInsensitive, QRegExp::FixedString));
        ui->twDiocesis->resizeRowsToContents();
        ui->twDiocesis->resizeColumnsToContents();
    }
}

void dlgDiocesis::menuContextualDiocesis(const QPoint &point)
{
    menuContextoDiocesis->popup(ui->twDiocesis->viewport()->mapToGlobal(point));
}

void dlgDiocesis::modificarDiocesis()
{
    if (diocesis_seleccionada == 0)
        return;

    dlgNuevaDiocesis *dlgnueva = new dlgNuevaDiocesis(diocesis_seleccionada, this);
    QMdiSubWindow *window = mdiarea->addSubWindow(dlgnueva);
    window->show();

}

void dlgDiocesis::anadirDetallesDiocesis()
{
    if (diocesis_seleccionada == 0)
        return;

    dlgDiocesisDetalles *dlgnueva = new dlgDiocesisDetalles(diocesis_seleccionada, this);
    QMdiSubWindow *window = mdiarea->addSubWindow(dlgnueva);
    window->show();

}

void dlgDiocesis::abrirUrl()
{
    QString url = extraerUrl();

    if (url.isEmpty()){
        qDebug() << "url está vacía";
        return;
    }

    QDesktopServices::openUrl(QUrl(url));

}

void dlgDiocesis::cerrar()
{
    parentWidget()->close();
}

void dlgDiocesis::on_ckSinComprobar_toggled(bool checked)
{
    if (checked)
        sql_gestor->anadirFiltro("comprobar", sql_comprobar);
    else
        sql_gestor->quitarFiltro("comprobar");
}

void dlgDiocesis::on_ckSinUrlHierarchy_toggled(bool checked)
{
    if (checked)
        sql_gestor->anadirFiltro("sinhierarchy", sql_sinhierarchy);
    else
        sql_gestor->quitarFiltro("sinhierarchy");

}

void dlgDiocesis::cargarModelos()
{
    m_diocesis->setQuery(sqlactivo);
    proxy_diocesis->setSourceModel(m_diocesis);

    ui->twDiocesis->setModel(proxy_diocesis);

    // ocultamos algunas columnas
    ui->twDiocesis->hideColumn(0);
    ui->twDiocesis->hideColumn(3);
    ui->twDiocesis->hideColumn(4);
    ui->twDiocesis->hideColumn(5);
    ui->twDiocesis->hideColumn(6);
    //ui->twDiocesis->hideColumn(7); esto es la nota
    ui->twDiocesis->hideColumn(8);
    ui->twDiocesis->hideColumn(9);
    ui->twDiocesis->hideColumn(10);
    ui->twDiocesis->hideColumn(11);
    ui->twDiocesis->hideColumn(12);
    ui->twDiocesis->hideColumn(13);

    ui->twDiocesis->setAlternatingRowColors(true);
    //ui->twResoluciones->setColumnWidth(1, 80);
    ui->twDiocesis->resizeColumnsToContents();
    ui->twDiocesis->resizeRowsToContents();
    ui->twDiocesis->horizontalHeader()->setStretchLastSection(true);
    ui->twDiocesis->setSortingEnabled(true);
    ui->twDiocesis->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twDiocesis->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twDiocesis->setAutoScroll(false);

    // escogemos la primera línea del modelo...
    QModelIndex index = proxy_diocesis->index(0,0);
    if (index.isValid()) {
        ui->twDiocesis->setCurrentIndex(index);
        seleccionarDiocesis(index);
    }

    ui->twObispos->setModel(m_obispos_proxy);
    ui->twObispos->resizeColumnsToContents();
    ui->twObispos->resizeRowsToContents();
    ui->twObispos->horizontalHeader()->setStretchLastSection(true);
    ui->twObispos->setSortingEnabled(true);
    ui->twObispos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twObispos->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->twObispos->hideColumn(0);
    ui->twObispos->hideColumn(1);
    ui->twObispos->hideColumn(6);
    ui->twObispos->hideColumn(10);
    ui->twObispos->hideColumn(11);
    ui->twObispos->hideColumn(12);
    ui->twObispos->hideColumn(13);
}

QString dlgDiocesis::extraerUrl()
{
    QSqlQuery query;
    QString url;

    query.prepare("SELECT other_data->'gcatholic'->>'url' FROM dioceses WHERE diocese_id = :diocesis");
    query.bindValue(":diocesis", diocesis_seleccionada);
    query.exec();

    query.next();
    url = query.value(0).toString();

    return url;

}

void dlgDiocesis::mostrarObispos()
{
    m_obispos_proxy->setFilterFixedString(QString::number(diocesis_seleccionada));
    m_obispos_proxy->setFilterKeyColumn(6);

    ui->twObispos->resizeColumnsToContents();
    ui->twObispos->resizeRowsToContents();
    ui->twObispos->horizontalHeader()->setStretchLastSection(true);
}

void dlgDiocesis::cargarMenus()
{
    menuContextoDiocesis = new QMenu(this);

    a_modificarDiocesis = new QAction("Modificar diócesis", this);
    connect(a_modificarDiocesis, SIGNAL(triggered(bool)), this, SLOT(modificarDiocesis()));

    menuContextoDiocesis->addAction(a_modificarDiocesis);
}

void dlgDiocesis::on_pbIntroducirObispos_clicked()
{
    QModelIndex indice= proxy_diocesis->index(ui->twDiocesis->currentIndex().row(), 0);
    if (!indice.isValid())
        return;

    int id = m_diocesis->data(proxy_diocesis->mapToSource(indice), Qt::DisplayRole).toInt();
    qDebug() << "escogido: " << id;

}

void dlgDiocesis::on_pbMarcarComprobado_clicked()
{
    QModelIndex indice1 = proxy_diocesis->index(ui->twDiocesis->currentIndex().row(), 13);
    QModelIndex indice2 = proxy_diocesis->index(ui->twDiocesis->currentIndex().row(), 0);
    if (!indice1.isValid() || !indice2.isValid() )
        return;
    bool vistos_todos = m_diocesis->data(proxy_diocesis->mapToSource(indice1), Qt::DisplayRole).toBool();
    int id = m_diocesis->data(proxy_diocesis->mapToSource(indice2), Qt::DisplayRole).toInt();

    vistos_todos = !vistos_todos;

    QSqlQuery query;
    query.prepare("UPDATE dioceses SET check_allbishops = :valor WHERE diocese_id = :id");
    query.bindValue(":valor", vistos_todos);
    query.bindValue(":id", id);

    if (!query.exec()){
        int ret = QMessageBox::warning(this, "Error",
                                       "Ha habido un error al ejecutar la consulta de inserción.");
        Q_UNUSED(ret)
        qDebug() << query.lastError();
        return;
    }
    else
    {
        m_diocesis->setQuery(sqlactivo);
    }


}
