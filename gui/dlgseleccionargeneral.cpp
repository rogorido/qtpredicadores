#include "dlgseleccionargeneral.h"
#include "ui_dlgseleccionargeneral.h"

#include "models/personasmodel.h"
#include "models/casasmodel.h"
#include "models/lugaresmodel.h"
#include "models/provinciasmodel.h"

#include "objs/proxynombres.h"

dlgSeleccionarGeneral::dlgSeleccionarGeneral(tiposeleccionar valor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSeleccionarGeneral), tipo_seleccionado(valor)
{
    ui->setupUi(this);

    // cargamos todos... aunque habría tal vez que hacerlo más profesional
    m_personas = PersonasModel::InstanceModel();
    m_casas = CasasModel::InstanceModel();
    m_lugares = LugaresModel::InstanceModel();
    m_provincias = ProvinciasModel::InstanceModel();

    connect(ui->btAnadir, SIGNAL(clicked(bool)), this, SLOT(anadirObjeto()));
    connect(ui->txtFiltro, SIGNAL(textEdited(QString)), this, SLOT(actualizarFiltro(QString)));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->twSeleccionar, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(aceptar()));
    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));

    cargarModelo();

}

dlgSeleccionarGeneral::~dlgSeleccionarGeneral()
{
    delete ui;
}

void dlgSeleccionarGeneral::cargarModelo(){

    m_objeto = new QSqlTableModel(this);

    switch (tipo_seleccionado) {
    case CASA:
        m_objeto->setTable("vistas.casas_alternativas");
        break;
    case LUGAR:
        m_objeto->setTable("vistas.lugares_alternativas");
    case PROVINCIA:
        m_objeto->setTable("vistas.provincias_alternativas");
    case PERSONA:
        m_objeto->setTable("vistas.personas_alternativas");
    default:
        break;
    }

    m_objeto->select();

    m_objeto_proxy = new ProxyNombres(2, this);
    m_objeto_proxy->setSourceModel(m_objeto);

    ui->twSeleccionar->setModel(m_objeto_proxy);
    ui->twSeleccionar->hideColumn(0);
    ui->twSeleccionar->setAlternatingRowColors(true);
    ui->twSeleccionar->resizeColumnsToContents();
    ui->twSeleccionar->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twSeleccionar->resizeRowsToContents();

    // escogemos la primera línea...
    QModelIndex index = m_objeto_proxy->index(0,0);
    ui->twSeleccionar->setCurrentIndex(index);
}


void dlgSeleccionarGeneral::actualizarFiltro(const QString filtro){

    if (filtro.length() > 2) {
        m_objeto_proxy->setFilterRegExp(QRegExp(filtro, Qt::CaseInsensitive, QRegExp::FixedString));
        ui->twSeleccionar->resizeRowsToContents();
    }
    else
    {
        m_objeto_proxy->setFilterRegExp(QRegExp("", Qt::CaseInsensitive, QRegExp::FixedString));
        ui->twSeleccionar->resizeRowsToContents();
    }
}

void dlgSeleccionarGeneral::aceptar(){

    // esto es un poco absurdo, tiene que haber otra manera...
    switch (tipo_seleccionado) {
    case CASA:
        casa();
        break;
    case LUGAR:
        lugar();
    case PROVINCIA:
        provincia();
    case PERSONA:
        persona();
    default:
        break;
    }
}

void dlgSeleccionarGeneral::casa(){
    /*
     * en teoría habría que emitir una casa, pero debido a que quiero construir
     * el nombre con la provincia, etc. sería más lío pq en el objeto Casa
     * tengo que poner lugar/provincia/etc. como int y luego tendría que convertirlo
     * en algún sitio a QString... por eso paso por ahora.
     */

    // tiene que haber otra manera de hacer esto...
    QModelIndex idx0 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 0);
    QModelIndex idx1 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 1);
    QModelIndex idx2 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 2);
    QModelIndex idx3 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 3);
    QModelIndex idx4 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 4);

    if (!idx0.isValid())
        return;

    int id = m_objeto->data(m_objeto_proxy->mapToSource(idx0), Qt::DisplayRole).toInt();
    QString nombre = m_objeto->data(m_objeto_proxy->mapToSource(idx1), Qt::DisplayRole).toString();
    QString lugar = m_objeto->data(m_objeto_proxy->mapToSource(idx2), Qt::DisplayRole).toString();
    QString provincia = m_objeto->data(m_objeto_proxy->mapToSource(idx3), Qt::DisplayRole).toString();
    QString advocacion = m_objeto->data(m_objeto_proxy->mapToSource(idx4), Qt::DisplayRole).toString();

    QString valor;

    // lo construimos de forma un poco cutre; esto habría que mejorarlo...
    valor = nombre;
    if (!lugar.isEmpty())
        valor += '-' + lugar;
    if (!provincia.isEmpty())
        valor += '-' + provincia;
    if (!advocacion.isEmpty())
        valor += '-' + advocacion;


    emit(casaEscogidaSignal(id, valor));
    close();
}

void dlgSeleccionarGeneral::lugar(){
    Lugar lugar;

    // tiene que haber otra manera de hacer esto...
    QModelIndex idx0 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 0);
    QModelIndex idx1 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 1);

    if (!idx0.isValid())
        return;

    int id = m_objeto->data(m_objeto_proxy->mapToSource(idx0), Qt::DisplayRole).toInt();
    QString lugarnombre = m_objeto->data(m_objeto_proxy->mapToSource(idx1), Qt::DisplayRole).toString();

    lugar.setId(id);
    lugar.setLugar(lugarnombre);

    emit(lugarEscogidoSignal(lugar));
    close();

}

void dlgSeleccionarGeneral::persona(){

    Persona autor;

    // tiene que haber otra manera de hacer esto...
    QModelIndex idx0 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 0);
    QModelIndex idx1 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 1);
    QModelIndex idx2 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 2);

    if (!idx0.isValid())
        return;

    int id = m_objeto->data(m_objeto_proxy->mapToSource(idx0), Qt::DisplayRole).toInt();
    QString nombre = m_objeto->data(m_objeto_proxy->mapToSource(idx1), Qt::DisplayRole).toString();
    QString apellidos = m_objeto->data(m_objeto_proxy->mapToSource(idx2), Qt::DisplayRole).toString();

    autor.setId(id);
    autor.setNombre(nombre);
    autor.setApellidos(apellidos);

    emit(personaEscogidaSignal(autor));
    close();
}
