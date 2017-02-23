#include "dlgseleccionarpersona.h"
#include "ui_dlgseleccionarpersona.h"

#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QRegExp>
#include <QSqlRecord>
#include <QDebug>

#include "personasmodel.h"
#include "nuevapersona.h"
#include "proxynombres.h"

dlgSeleccionarPersona::dlgSeleccionarPersona(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSeleccionarPersona)
{
    ui->setupUi(this);

    m_personas = PersonasModel::InstanceModel();

    connect(ui->btAnadirPersona, SIGNAL(clicked(bool)), this, SLOT(anadirPersona()));
    connect(ui->txtFiltroPersona, SIGNAL(textEdited(QString)), this, SLOT(actualizarFiltro(QString)));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
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

void dlgSeleccionarPersona::aceptar(){

    Persona autor;

    // tiene que haber otra manera de hacer esto...
    QModelIndex idx0 = m_nombres_proxy->index(ui->twPersonas->currentIndex().row(), 0);
    QModelIndex idx1 = m_nombres_proxy->index(ui->twPersonas->currentIndex().row(), 1);
    QModelIndex idx2 = m_nombres_proxy->index(ui->twPersonas->currentIndex().row(), 2);

    if (!idx0.isValid())
        return;

    int id = m_nombres->data(m_nombres_proxy->mapToSource(idx0), Qt::DisplayRole).toInt();
    QString nombre = m_nombres->data(m_nombres_proxy->mapToSource(idx1), Qt::DisplayRole).toString();
    QString apellidos = m_nombres->data(m_nombres_proxy->mapToSource(idx2), Qt::DisplayRole).toString();

    autor.setId(id);
    autor.setNombre(nombre);
    autor.setApellidos(apellidos);

    emit(personaEscogida(autor));
    close();
}
