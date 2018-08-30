#include "dlggestionpersonas.h"
#include "ui_dlggestionpersonas.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QMdiSubWindow>

#include "gui/dlgnuevapersona.h"
#include "widgets/myqmdiarea.h"

#include "models/sqlfiltrogestor.h"

const QString sql_general = "SELECT * FROM vistas.p_persons_general";

// no me acuerdo por qué hago esto así en lugar de contar las rows del modelo...
const QString sqlcontar = "SELECT count(*) FROM vistas.p_persons_general";


dlgGestionPersonas::dlgGestionPersonas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgGestionPersonas)
{
    ui->setupUi(this);
    mdiarea = MyQmdiArea::Instance(this);

    // no recuerdo por qué guardo esto en esta variable...
    sqlactivo = sql_general;

    m_persons = new QSqlQueryModel(this);

    sql_gestor = new SqlFiltroGestor(sql_general, this);
    connect(sql_gestor, SIGNAL(actualizadoSqlFiltroGestor(QString)), this, SLOT(actualizarSql(QString)));

    cargarModelos();
    cargarMenus();

    ui->tvPersonas->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->tvPersonas, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(menuContextual(const QPoint &)));

    /*
     * esto lo hacemos aquí aunque luego hay una función con
     * este mismo código. Pero el asunto es que esto necesito
     * hacerlo al cargar el formulario para que meta en esa variable
     * el total. Aunque sospecho que esto es una cutrada.
     */
    QSqlQuery query(sqlcontar);
    query.next();
    total_personas = query.value(0).toInt();
    emitirSenalTotalPersonas();

}

dlgGestionPersonas::~dlgGestionPersonas()
{
    delete ui;
}

void dlgGestionPersonas::contarTotal()
{
    //total_filtrado = obispos_model->rowCount();
    total_filtrado = m_persons->rowCount();

    emitirSenalTotalPersonas();

}

void dlgGestionPersonas::menuContextual(const QPoint &point)
{
    menuContexto->popup(ui->tvPersonas->viewport()->mapToGlobal(point));

}

void dlgGestionPersonas::actualizarSql(QString s)
{
    sqlactivo = s;

    m_persons->setQuery(sqlactivo);

    contarTotal();
}

void dlgGestionPersonas::modificarPersona()
{
    QModelIndex idx = ui->tvPersonas->currentIndex();

    if (!idx.isValid())
        return;

    int row = ui->tvPersonas->currentIndex().row();
    idx = m_persons->index(row, 0);
    if (!idx.isValid())
        return;
    person_id = m_persons->data(idx, Qt::DisplayRole).toInt();

    qDebug() << "la id es..." << person_id;

    dlgPersonaAModificar = new dlgNuevaPersona(this, person_id);
    QMdiSubWindow *window = mdiarea->addSubWindow(dlgPersonaAModificar);
    connect(dlgPersonaAModificar, SIGNAL(personaIntroducida()), this, SLOT(actualizarModeloTrasPersonaActualizada()));
    window->show();
}

void dlgGestionPersonas::emitirSenalTotalPersonas()
{
    QString final;

   if (total_personas == total_filtrado){
       final = QString("Personas: %1").arg(total_personas);
   }
   else {
       final = QString("Personas: %1/%2").arg(QString::number(total_filtrado)).arg(total_personas);
   }
   emit infoBarraInferior(final);
}

void dlgGestionPersonas::actualizarModeloTrasPersonaActualizada()
{
    m_persons->setQuery(sqlactivo);
    contarTotal();

}

void dlgGestionPersonas::cargarMenus()
{
    menuContexto = new QMenu(this);

    a_cambiarPersona = new QAction("Modificar persona", this);
    connect(a_cambiarPersona, SIGNAL(triggered(bool)), this, SLOT(modificarPersona()));
    menuContexto->addAction(a_cambiarPersona);
 }

void dlgGestionPersonas::cargarModelos()
{
    m_persons->setQuery(sqlactivo);
    ui->tvPersonas->setModel(m_persons);

    ui->tvPersonas->setAlternatingRowColors(true);
    //ui->twResoluciones->setColumnWidth(1, 80);
    ui->tvPersonas->resizeColumnsToContents();
    ui->tvPersonas->resizeRowsToContents();
    ui->tvPersonas->horizontalHeader()->setStretchLastSection(true);
    ui->tvPersonas->setSortingEnabled(true);
    ui->tvPersonas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvPersonas->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvPersonas->hideColumn(0);

    // escogemos la primera línea del modelo...
    QModelIndex index = m_persons->index(0,0);
    if (index.isValid()) {
        ui->tvPersonas->setCurrentIndex(index);
    }

}
