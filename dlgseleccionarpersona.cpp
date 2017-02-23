#include "dlgseleccionarpersona.h"
#include "ui_dlgseleccionarpersona.h"

#include "personasmodel.h"
#include "nuevapersona.h"
#include "proxynombres.h"

#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QRegExp>

dlgSeleccionarPersona::dlgSeleccionarPersona(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSeleccionarPersona)
{
    ui->setupUi(this);

    m_personas = PersonasModel::InstanceModel();

    connect(ui->btAnadirPersona, SIGNAL(clicked(bool)), this, SLOT(anadirPersona()));
    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->txtFiltroPersona, SIGNAL(textEdited(QString)), this, SLOT(actualizarFiltro(QString)));

    cargarModelo();
}

dlgSeleccionarPersona::~dlgSeleccionarPersona()
{
    delete ui;
}

void dlgSeleccionarPersona::anadirPersona(){

    NuevaPersona *persona = new NuevaPersona(this);
    persona->show();
}

void dlgSeleccionarPersona::cargarModelo(){

    m_nombres = new QSqlTableModel(this);
    m_nombres->setTable("vistas.nombres_alternativas");
    m_nombres->select();

    m_nombres_proxy = new ProxyNombres(this);
    m_nombres_proxy->setSourceModel(m_nombres);

    ui->twPersonas->setModel(m_nombres_proxy);
    ui->twPersonas->hideColumn(0);
    ui->twPersonas->setAlternatingRowColors(true);
    ui->twPersonas->resizeColumnsToContents();
    ui->twPersonas->setSelectionBehavior(QAbstractItemView::SelectRows);

    // escogemos la primera línea...
    QModelIndex index = m_nombres_proxy->index(0,0);
    ui->twPersonas->setCurrentIndex(index);
}

void dlgSeleccionarPersona::actualizarFiltro(const QString filtro){

    if (filtro.length() > 3) {
        m_nombres_proxy->setFilterRegExp(QRegExp(filtro, Qt::CaseInsensitive, QRegExp::FixedString));
    }
    else
    {
        m_nombres_proxy->setFilterRegExp(QRegExp("", Qt::CaseInsensitive, QRegExp::FixedString));
    }
}
