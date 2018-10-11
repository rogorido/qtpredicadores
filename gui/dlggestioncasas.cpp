#include "dlggestioncasas.h"
#include "ui_dlggestioncasas.h"

#include <QDebug>
#include <QMdiSubWindow>

#include "models/casasmodel.h"

#include "models/sqlfiltrogestor.h"
#include "objs/proxynombres.h"
#include "gui/dlgnuevacasa.h"
#include "widgets/myqmdiarea.h"

const QString sql_general = "SELECT * from vistas.houses_alternatives";

dlgGestionCasas::dlgGestionCasas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgGestionCasas)
{
    ui->setupUi(this);
    mdiarea = MyQmdiArea::Instance(this);

    sqlactivo = sql_general;

    sql_gestor = new SqlFiltroGestor(sql_general, this);

    connect(sql_gestor, SIGNAL(actualizadoSqlFiltroGestor(QString)), this, SLOT(actualizarSql(QString)));

    cargarModelos();

    connect(ui->twCasas->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            this, SLOT(seleccionarCasa(QModelIndex)));
    connect(ui->txtFiltro, SIGNAL(textEdited(QString)), this, SLOT(actualizarFiltro(QString)));

    connect(ui->btCerrar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
}

dlgGestionCasas::~dlgGestionCasas()
{
    delete ui;
}

void dlgGestionCasas::actualizarFiltro(const QString filtro)
{
    if (filtro.length() > 2) {
        proxy_casas->setFilterRegExp(QRegExp(filtro, Qt::CaseInsensitive, QRegExp::FixedString));
        ui->twCasas->resizeRowsToContents();
        ui->twCasas->resizeColumnsToContents();
        //contarTotal();
    }
    else
    {
        proxy_casas->setFilterRegExp(QRegExp("", Qt::CaseInsensitive, QRegExp::FixedString));
        ui->twCasas->resizeRowsToContents();
        ui->twCasas->resizeColumnsToContents();
        //contarTotal();
    }
}

void dlgGestionCasas::seleccionarCasa(const QModelIndex &idx)
{
    Q_UNUSED(idx)
    // NOTE: aquí no estoy usando lo de idx... he cogido este código de lo de modificar persona...
    QModelIndex indice= proxy_casas->index(ui->twCasas->currentIndex().row(), 0);
    if (!indice.isValid())
        return;

    int id = m_casas->data(proxy_casas->mapToSource(indice), Qt::DisplayRole).toInt();
    qDebug() << "estamos escogiendo la casa: " << id;

    //QString mensaje = QString("Persona_id: ") + QString::number(id);
    //emit infoPersonaSeleccionada(mensaje);


}

void dlgGestionCasas::actualizarModeloTrasCasaIntroducida()
{
    m_casas->setQuery(sqlactivo);
}

void dlgGestionCasas::actualizarSql(QString s)
{
    sqlactivo = s;

    m_casas->setQuery(sqlactivo);
    ui->twCasas->resizeColumnsToContents();
    ui->twCasas->resizeRowsToContents();

}

void dlgGestionCasas::cerrar()
{
    parentWidget()->close();
}

void dlgGestionCasas::cargarModelos(){

    m_casas = CasasModel::InstanceModel();
    m_casas->setQuery(sqlactivo);

    proxy_casas = new ProxyNombres(CASASGESTION, this);
    proxy_casas->setSourceModel(m_casas);

    ui->twCasas->setModel(proxy_casas);
    ui->twCasas->hideColumn(0);
    ui->twCasas->hideColumn(2);

    ui->twCasas->setSortingEnabled(true);
    ui->twCasas->resizeColumnsToContents();
    ui->twCasas->resizeRowsToContents();
    ui->twCasas->setAlternatingRowColors(true);
    ui->twCasas->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twCasas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twCasas->horizontalHeader()->setStretchLastSection(true);

    proxy_casas->sort(1, Qt::AscendingOrder);

    ui->twCasas->resizeColumnsToContents();
    ui->twCasas->resizeRowsToContents();

    // escogemos la primera línea del modelo...
    QModelIndex index = proxy_casas->index(0,0);
    if (index.isValid()) {
        ui->twCasas->setCurrentIndex(index);
    }


}

void dlgGestionCasas::on_btModificar_clicked()
{
    QModelIndex indice= proxy_casas->index(ui->twCasas->currentIndex().row(), 0);
    if (!indice.isValid())
        return;

    int id = m_casas->data(proxy_casas->mapToSource(indice), Qt::DisplayRole).toInt();
    qDebug() << "escogido: " << id;

    dlgCasaAModificar = new dlgNuevaCasa(this, id);
    QMdiSubWindow *window = mdiarea->addSubWindow(dlgCasaAModificar);
    connect(dlgCasaAModificar, SIGNAL(casaIntroducida()), this, SLOT(actualizarModeloTrasCasaIntroducida));
    window->show();
}

void dlgGestionCasas::on_rbFemeninas_toggled(bool checked)
{
    if (checked) {
        sql_gestor->anadirFiltro("femeninas", "men = FALSE");
        sql_gestor->quitarFiltro("masculinas");
    }
    else
        sql_gestor->quitarFiltro("femeninas");

}

void dlgGestionCasas::on_rbMasculinas_toggled(bool checked)
{
    if (checked) {
        sql_gestor->anadirFiltro("masculinas", "men = TRUE");
        sql_gestor->quitarFiltro("femeninas");
    }
    else
        sql_gestor->quitarFiltro("masculinas");

}

void dlgGestionCasas::on_rbTodas_toggled(bool checked)
{
    sql_gestor->quitarFiltro("masculinas");
    sql_gestor->quitarFiltro("femeninas");

}
