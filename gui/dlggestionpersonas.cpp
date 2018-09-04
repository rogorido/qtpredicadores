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
#include "models/personasmodel.h"
#include "models/sqlfiltrogestor.h"
#include "objs/proxynombres.h"

const QString sql_general = "SELECT * FROM vistas.persons_alternatives";

// no me acuerdo por qué hago esto así en lugar de contar las rows del modelo...
const QString sqlcontar = "SELECT count(*) FROM vistas.persons_altenatives";


dlgGestionPersonas::dlgGestionPersonas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgGestionPersonas)
{
    ui->setupUi(this);
    mdiarea = MyQmdiArea::Instance(this);

    // no recuerdo por qué guardo esto en esta variable...
    sqlactivo = sql_general;

    m_persons = PersonasModel::InstanceModel();

    sql_gestor = new SqlFiltroGestor(sql_general, this);
    connect(sql_gestor, SIGNAL(actualizadoSqlFiltroGestor(QString)), this, SLOT(actualizarSql(QString)));

    cargarModelos();
    cargarMenus();

    ui->tvPersonas->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tvPersonas->verticalHeader()->hide();

    connect(ui->tvPersonas, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(menuContextual(const QPoint &)));
    connect(ui->tvPersonas->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(seleccionarPersona(QModelIndex)));

    connect(ui->txtFiltro, SIGNAL(textEdited(QString)), this, SLOT(actualizarFiltro(QString)));

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
    emit infoPersonaSeleccionadaBorrar();
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

void dlgGestionPersonas::actualizarFiltro(const QString filtro)
{
    if (filtro.length() > 2) {
        proxy_personas->setFilterRegExp(QRegExp(filtro, Qt::CaseInsensitive, QRegExp::FixedString));
        ui->tvPersonas->resizeRowsToContents();
        ui->tvPersonas->resizeColumnsToContents();
        contarTotal();
    }
    else
    {
        proxy_personas->setFilterRegExp(QRegExp("", Qt::CaseInsensitive, QRegExp::FixedString));
        ui->tvPersonas->resizeRowsToContents();
        ui->tvPersonas->resizeColumnsToContents();
        contarTotal();
    }
}

void dlgGestionPersonas::actualizarSql(const QString s)
{
    sqlactivo = s;

    m_persons->setQuery(sqlactivo);

    contarTotal();
}

void dlgGestionPersonas::modificarPersona()
{
    QModelIndex indice= proxy_personas->index(ui->tvPersonas->currentIndex().row(), 0);
    if (!indice.isValid())
        return;

    int id = m_persons->data(proxy_personas->mapToSource(indice), Qt::DisplayRole).toInt();
   // qDebug() << "escogido: " << id;

    dlgPersonaAModificar = new dlgNuevaPersona(this, id);
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

void dlgGestionPersonas::seleccionarPersona(const QModelIndex &idx)
{
    Q_UNUSED(idx)
    // NOTE: aquí no estoy usando lo de idx... he cogido este código de lo de modificar persona...
    QModelIndex indice= proxy_personas->index(ui->tvPersonas->currentIndex().row(), 0);
    if (!indice.isValid())
        return;

    int id = m_persons->data(proxy_personas->mapToSource(indice), Qt::DisplayRole).toInt();
    qDebug() << "escogido: " << id;

    QString mensaje = QString("Persona_id: ") + QString::number(id);
    emit infoPersonaSeleccionada(mensaje);

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

    proxy_personas = new ProxyNombres(PERSONASGESTION, this);
    proxy_personas->setSourceModel(m_persons);

    ui->tvPersonas->setModel(proxy_personas);

    ui->tvPersonas->setAlternatingRowColors(true);
    //ui->twResoluciones->setColumnWidth(1, 80);
    ui->tvPersonas->resizeColumnsToContents();
    ui->tvPersonas->resizeRowsToContents();
    ui->tvPersonas->horizontalHeader()->setStretchLastSection(true);
    ui->tvPersonas->setSortingEnabled(true);
    ui->tvPersonas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvPersonas->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvPersonas->hideColumn(0);
    ui->tvPersonas->hideColumn(4); // esto es lo de male

    // escogemos la primera línea del modelo...
    QModelIndex index = proxy_personas->index(0,0);
    if (index.isValid()) {
        ui->tvPersonas->setCurrentIndex(index);
    }

}
