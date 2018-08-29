#include "dlggestionobras.h"
#include "ui_dlggestionobras.h"

#include <QSqlQuery>
#include <QSqlQueryModel>

#include "models/sqlfiltrogestor.h"

const QString sql_general = "SELECT * FROM vistas.w_works_general";

// no me acuerdo por qué hago esto así en lugar de contar las rows del modelo...
const QString sqlcontar = "SELECT count(*) FROM vistas.w_works_general";

dlgGestionObras::dlgGestionObras(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgGestionObras)
{
    ui->setupUi(this);

    // no recuerdo por qué guardo esto en esta variable...
    sqlactivo = sql_general;

    works_model = new QSqlQueryModel(this);

    sql_gestor = new SqlFiltroGestor(sql_general, this);
    connect(sql_gestor, SIGNAL(actualizadoSqlFiltroGestor(QString)), this, SLOT(actualizarSql(QString)));

    cargarModelos();

    /*
     * esto lo hacemos aquí aunque luego hay una función con
     * este mismo código. Pero el asunto es que esto necesito
     * hacerlo al cargar el formulario para que meta en esa variable
     * el total. Aunque sospecho que esto es una cutrada.
     */
    QSqlQuery query(sqlcontar);
    query.next();
    total_obras = query.value(0).toInt();
    emitirSenalTotalObras();

}

dlgGestionObras::~dlgGestionObras()
{
    delete ui;
}

void dlgGestionObras::contarTotal()
{
    //total_filtrado = obispos_model->rowCount();
    total_filtrado = works_model->rowCount();

    emitirSenalTotalObras();
}

void dlgGestionObras::on_rbManuscritos_clicked()
{
    sql_gestor->quitarFiltro("publicado");
    sql_gestor->anadirFiltro("manuscrito", "manuscrit = TRUE");
}

void dlgGestionObras::actualizarSql(QString s)
{
    sqlactivo = s;

    works_model->setQuery(sqlactivo);

    contarTotal();
}

void dlgGestionObras::emitirSenalTotalObras()
{
    QString final;

   if (total_obras == total_filtrado){
       final = QString("Obras: %1").arg(total_obras);
   }
   else {
       final = QString("Obras: %1/%2").arg(QString::number(total_filtrado)).arg(total_obras);
   }
   emit infoBarraInferior(final);
}

void dlgGestionObras::cargarMenus()
{

}

void dlgGestionObras::cargarModelos()
{
    works_model->setQuery(sqlactivo);
    ui->tvObras->setModel(works_model);

    ui->tvObras->setAlternatingRowColors(true);
    //ui->twResoluciones->setColumnWidth(1, 80);
    ui->tvObras->resizeColumnsToContents();
    ui->tvObras->resizeRowsToContents();
    ui->tvObras->horizontalHeader()->setStretchLastSection(true);
    ui->tvObras->setSortingEnabled(true);
    ui->tvObras->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvObras->setSelectionMode(QAbstractItemView::SingleSelection);

    // escogemos la primera línea del modelo...
    QModelIndex index = works_model->index(0,0);
    if (index.isValid()) {
        ui->tvObras->setCurrentIndex(index);
    }
}

void dlgGestionObras::on_rbImpresos_clicked()
{
    sql_gestor->quitarFiltro("manuscrito");
    sql_gestor->anadirFiltro("publicado", "printed = TRUE");
}

void dlgGestionObras::on_rbTodos_clicked()
{
    sql_gestor->quitarFiltro("manuscrito");
    sql_gestor->quitarFiltro("publicado");

}

void dlgGestionObras::on_ckSinMateria_stateChanged(int arg1)
{
    if (ui->ckSinMateria->checkState() == Qt::Checked)
        sql_gestor->anadirFiltro("sinmaterias", "work_id NOT IN (SELECT DISTINCT work_id FROM works_themes)");
    else
        sql_gestor->quitarFiltro("sinmaterias");
}
