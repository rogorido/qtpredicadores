#include "dlgseleccionarlugar.h"
#include "ui_dlgseleccionarlugar.h"

#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QRegExp>

#include "lugaresmodel.h"
#include "proxynombres.h"

dlgSeleccionarLugar::dlgSeleccionarLugar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSeleccionarLugar)
{
    ui->setupUi(this);

    m_lugares = LugaresModel::InstanceModel();

    connect(ui->btAnadirLugar, SIGNAL(clicked(bool)), this, SLOT(anadirLugar()));
    connect(ui->txtFiltroLugar, SIGNAL(textEdited(QString)), this, SLOT(actualizarFiltro(QString)));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->twLugares, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(aceptar()));
    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));

    cargarModelo();
}

dlgSeleccionarLugar::~dlgSeleccionarLugar()
{
    delete ui;
}

void dlgSeleccionarLugar::anadirLugar(){

    NuevaLugar *persona = new NuevaLugar(this);
    persona->show();
}

void dlgSeleccionarLugar::cargarModelo(){

    m_lugares_base = new QSqlTableModel(this);
    m_lugares_base->setTable("vistas.nombres_alternativas");
    m_lugares_base->select();

    m_lugares_proxy = new ProxyNombres(1, this);
    m_lugares_proxy->setSourceModel(m_lugares_base);

    ui->twLugares->setModel(m_lugares_proxy);
    ui->twLugares->hideColumn(0);
    ui->twLugares->setAlternatingRowColors(true);
    ui->twLugares->resizeColumnsToContents();
    ui->twLugares->setSelectionBehavior(QAbstractItemView::SelectRows);

    // escogemos la primera línea...
    QModelIndex index = m_lugares_proxy->index(0,0);
    ui->twLugares->setCurrentIndex(index);
}

void dlgSeleccionarLugar::actualizarFiltro(const QString filtro){

    if (filtro.length() > 3) {
        m_lugares_proxy->setFilterRegExp(QRegExp(filtro, Qt::CaseInsensitive, QRegExp::FixedString));
    }
    else
    {
        m_lugares_proxy->setFilterRegExp(QRegExp("", Qt::CaseInsensitive, QRegExp::FixedString));
    }
}

void dlgSeleccionarLugar::aceptar(){

    Lugar autor;

    // tiene que haber otra manera de hacer esto...
    QModelIndex idx0 = m_lugares_proxy->index(ui->twLugares->currentIndex().row(), 0);
    QModelIndex idx1 = m_lugares_proxy->index(ui->twLugares->currentIndex().row(), 1);
    QModelIndex idx2 = m_lugares_proxy->index(ui->twLugares->currentIndex().row(), 2);

    if (!idx0.isValid())
        return;

    int id = m_lugares_base->data(m_lugares_proxy->mapToSource(idx0), Qt::DisplayRole).toInt();
    QString nombre = m_lugares_base->data(m_lugares_proxy->mapToSource(idx1), Qt::DisplayRole).toString();
    QString apellidos = m_lugares_base->data(m_lugares_proxy->mapToSource(idx2), Qt::DisplayRole).toString();

    autor.setId(id);
    autor.setNombre(nombre);
    autor.setApellidos(apellidos);

    emit(personaEscogida(autor));
    close();
}
