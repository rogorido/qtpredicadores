#include "dlgseleccionarcasa.h"
#include "ui_dlgseleccionarcasa.h"

#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QRegExp>
#include <QDebug>

#include "models/casasmodel.h"
#include "dlgnuevacasa.h"
#include "objs/proxynombres.h"

dlgSeleccionarCasa::dlgSeleccionarCasa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSeleccionarCasa)
{
    ui->setupUi(this);

    m_casas = CasasModel::InstanceModel();

    connect(ui->btAnadirCasa, SIGNAL(clicked(bool)), this, SLOT(anadirCasa()));
    connect(ui->txtFiltroCasa, SIGNAL(textEdited(QString)), this, SLOT(actualizarFiltro(QString)));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->twCasas, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(aceptar()));
    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));

    cargarModelo();
}

dlgSeleccionarCasa::~dlgSeleccionarCasa()
{
    delete ui;
}

void dlgSeleccionarCasa::anadirCasa(){

    dlgNuevaCasa *casa = new dlgNuevaCasa(this);
    casa->show();
}

void dlgSeleccionarCasa::cargarModelo(){

    m_nombres = new QSqlTableModel(this);
    m_nombres->setTable("vistas.nombres_alternativas");
    m_nombres->select();

    m_nombres_proxy = new ProxyNombres(0, this);
    m_nombres_proxy->setSourceModel(m_nombres);

    ui->twCasas->setModel(m_nombres_proxy);
    ui->twCasas->hideColumn(0);
    ui->twCasas->setAlternatingRowColors(true);
    ui->twCasas->resizeColumnsToContents();
    ui->twCasas->setSelectionBehavior(QAbstractItemView::SelectRows);

    // escogemos la primera línea...
    QModelIndex index = m_nombres_proxy->index(0,0);
    ui->twCasas->setCurrentIndex(index);
}

void dlgSeleccionarCasa::actualizarFiltro(const QString filtro){

    if (filtro.length() > 3) {
        m_nombres_proxy->setFilterRegExp(QRegExp(filtro, Qt::CaseInsensitive, QRegExp::FixedString));
    }
    else
    {
        m_nombres_proxy->setFilterRegExp(QRegExp("", Qt::CaseInsensitive, QRegExp::FixedString));
    }
}

void dlgSeleccionarCasa::aceptar(){

    Casa casa;

    // tiene que haber otra manera de hacer esto...
    QModelIndex idx0 = m_nombres_proxy->index(ui->twCasas->currentIndex().row(), 0);
    QModelIndex idx1 = m_nombres_proxy->index(ui->twCasas->currentIndex().row(), 1);
    QModelIndex idx2 = m_nombres_proxy->index(ui->twCasas->currentIndex().row(), 2);

    if (!idx0.isValid())
        return;

    int id = m_nombres->data(m_nombres_proxy->mapToSource(idx0), Qt::DisplayRole).toInt();
    QString nombre = m_nombres->data(m_nombres_proxy->mapToSource(idx1), Qt::DisplayRole).toString();

    casa.setId(id);
    casa.setNombre(nombre);

    emit(casaEscogida(casa));
    close();
}
