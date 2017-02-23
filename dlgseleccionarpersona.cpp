#include "dlgseleccionarpersona.h"
#include "ui_dlgseleccionarpersona.h"

#include "personasmodel.h"
#include "nuevapersona.h"

#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>

dlgSeleccionarPersona::dlgSeleccionarPersona(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSeleccionarPersona)
{
    ui->setupUi(this);

    m_personas = PersonasModel::InstanceModel();

    connect(ui->btAnadirPersona, SIGNAL(clicked(bool)), this, SLOT(anadirPersona()));
    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));

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
}
