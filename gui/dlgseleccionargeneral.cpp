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
