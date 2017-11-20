#include "dlgdiocesis.h"
#include "ui_dlgdiocesis.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "models/sqlfiltrogestor.h"
#include "objs/proxynombres.h"

const QString sqlgeneral = "SELECT * from general.dioceses";
const QString sqlcomprobar = "check_allbishops = false";

dlgDiocesis::dlgDiocesis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgDiocesis)
{
    ui->setupUi(this);

    menuContexto = new QMenu(this);

    m_diocesis = new QSqlQueryModel(this);
    sqlactivo = sqlgeneral;

    sql_gestor = new SqlFiltroGestor(sqlgeneral, this);
    connect(sql_gestor, SIGNAL(actualizadoSqlFiltroGestor(QString)), this, SLOT(actualizarSql(QString)));

    cargarModelos();

    connect(ui->pbCerrar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    connect(ui->twDiocesis->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(seleccionarDiocesis(QModelIndex)));
    connect(ui->txtFiltro, SIGNAL(textEdited(QString)), this, SLOT(actualizarFiltro(QString)));
    connect(ui->pbAbrirUrl, SIGNAL(clicked()), this, SLOT(abrirUrl()));

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

    diocesis_seleccionada = m_diocesis->data(indice_verdadero, Qt::DisplayRole).toInt();
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
        sql_gestor->anadirFiltro("comprobar", sqlcomprobar);
    else
        sql_gestor->quitarFiltro("comprobar");
}

void dlgDiocesis::cargarModelos()
{
    m_diocesis->setQuery(sqlactivo);
    proxy_diocesis = new ProxyNombres(DIOCESIS, this);
    proxy_diocesis->setSourceModel(m_diocesis);

    ui->twDiocesis->setModel(proxy_diocesis);

    // ocultamos algunas columnas
    ui->twDiocesis->hideColumn(0);
    ui->twDiocesis->hideColumn(3);
    ui->twDiocesis->hideColumn(4);
    ui->twDiocesis->hideColumn(5);
    ui->twDiocesis->hideColumn(6);
    ui->twDiocesis->hideColumn(7);
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

    // escogemos la primera línea del modelo...
    QModelIndex index = proxy_diocesis->index(0,0);
    if (index.isValid()) {
        ui->twDiocesis->setCurrentIndex(index);
    }
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
