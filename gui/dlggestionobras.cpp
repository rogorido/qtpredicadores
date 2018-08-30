#include "dlggestionobras.h"
#include "ui_dlggestionobras.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QMdiSubWindow>

#include "gui/dlgnuevaobra.h"
#include "gui/dlgseleccionargeneral.h"

#include "widgets/myqmdiarea.h"

#include "models/sqlfiltrogestor.h"

const QString sql_general = "SELECT * FROM vistas.w_works_general";

// no me acuerdo por qué hago esto así en lugar de contar las rows del modelo...
const QString sqlcontar = "SELECT count(*) FROM vistas.w_works_general";

dlgGestionObras::dlgGestionObras(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgGestionObras)
{
    ui->setupUi(this);
    mdiarea = MyQmdiArea::Instance(this);

    // no recuerdo por qué guardo esto en esta variable...
    sqlactivo = sql_general;

    works_model = new QSqlQueryModel(this);

    sql_gestor = new SqlFiltroGestor(sql_general, this);
    connect(sql_gestor, SIGNAL(actualizadoSqlFiltroGestor(QString)), this, SLOT(actualizarSql(QString)));

    cargarModelos();
    cargarMenus();

    ui->tvObras->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->tvObras, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(menuContextual(const QPoint &)));

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
    window->show();
}

void dlgGestionObras::verPersona()
{

}

void dlgGestionObras::modificarPersona()
{

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

void dlgGestionObras::recibirTema(Tema tema)
{
    elementopareado nuevotema;

    nuevotema.id = tema.getId();
    nuevotema.elemento = tema.getTema();

    materias_escogidas.append(nuevotema);
    QListWidgetItem *item = new QListWidgetItem(nuevotema.elemento, ui->lwTemas);

    generarSQLMaterias();

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

void dlgGestionObras::generarSQLMaterias()
{
    QString sql;

    if (materias_escogidas.size() == 0) {
        sql_gestor->quitarFiltro("materias");
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

    sql_gestor->anadirFiltro("materias", sql);

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
    Q_UNUSED(arg1)

    if (ui->ckSinMateria->checkState() == Qt::Checked)
        sql_gestor->anadirFiltro("sinmaterias", "work_id NOT IN (SELECT DISTINCT work_id FROM works_themes)");
    else
        sql_gestor->quitarFiltro("sinmaterias");
}

void dlgGestionObras::menuContextual(const QPoint &point)
{
    menuContexto->popup(ui->tvObras->viewport()->mapToGlobal(point));
}

void dlgGestionObras::on_pbAnadirTema_clicked()
{
    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(TEMA, this);

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
    //ui->lwTemas->removeItemWidget(ui->lwTemas->currentItem());

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
