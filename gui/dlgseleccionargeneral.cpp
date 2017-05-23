#include "dlgseleccionargeneral.h"
#include "ui_dlgseleccionargeneral.h"

#include "models/personasmodel.h"
#include "models/casasmodel.h"
#include "models/lugaresmodel.h"
#include "models/provinciasmodel.h"
#include "models/capitulosmodel.h"
#include "models/temasmodel.h"
#include "models/diocesismodel.h"

#include "objs/proxynombres.h"

#include "gui/dlgnuevacasa.h"
#include "gui/dlgnuevapersona.h"
#include "gui/dlgnuevaprovincia.h"
#include "gui/dlgnuevolugar.h"
#include "gui/dlgnuevocapitulo.h"
#include "gui/dlgnuevadiocesis.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>

dlgSeleccionarGeneral::dlgSeleccionarGeneral(tiposeleccionar valor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSeleccionarGeneral), tipo_seleccionado(valor)
{
    ui->setupUi(this);

    ui->txtFiltro->setClearButtonEnabled(true);

    connect(ui->btAnadir, SIGNAL(clicked(bool)), this, SLOT(anadirObjeto()));
    connect(ui->txtFiltro, SIGNAL(textEdited(QString)), this, SLOT(actualizarFiltro(QString)));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->twSeleccionar, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(aceptar()));
    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));

    cargarTipo();
    cargarModelo();
}

dlgSeleccionarGeneral::~dlgSeleccionarGeneral()
{
    delete ui;
}

void dlgSeleccionarGeneral::cargarTipo(){
    m_objeto = new QSqlTableModel(this);

    switch (tipo_seleccionado) {
    case CASA:{
        m_casas = CasasModel::InstanceModel();
        m_objeto->setTable("vistas.houses_alternatives");
        ui->btAnadir->setText("Aña&dir casa");
        connect(m_casas, SIGNAL(actualizado()), this, SLOT(actualizarObjeto()));
        break;}
    case LUGAR:{
        m_lugares = LugaresModel::InstanceModel();
        m_objeto->setTable("vistas.places_alternatives");
        ui->btAnadir->setText("Aña&dir lugar");
        connect(m_lugares, SIGNAL(actualizado()), this, SLOT(actualizarObjeto()));
        break;}
    case PROVINCIA:{
        m_provincias = ProvinciasModel::InstanceModel();
        m_objeto->setTable("vistas.provinces_alternatives");
        ui->btAnadir->setText("Aña&dir provincia");
        connect(m_provincias, SIGNAL(actualizado()), this, SLOT(actualizarObjeto()));
        break;}
    case PERSONA:{
        m_personas = PersonasModel::InstanceModel();
        m_objeto->setTable("vistas.persons_alternatives");
        ui->btAnadir->setText("Aña&dir persona");
        connect(m_personas, SIGNAL(actualizado()), this, SLOT(actualizarObjeto()));
        break;}
    case CAPITULO:{
        m_capitulos = CapitulosModel::InstanceModel();
        m_objeto->setTable("vistas.chapters_alternatives");
        ui->btAnadir->setText("Aña&dir capítulo");
        connect(m_capitulos, SIGNAL(actualizado()), this, SLOT(actualizarObjeto()));
        break;}
    case DIOCESIS:{
        m_diocesis = DiocesisModel::InstanceModel();
        m_objeto->setTable("vistas.dioceses_alternatives");
        comprobarVacio();
        ui->btAnadir->setText("Aña&dir diócesis");
        connect(m_diocesis, SIGNAL(actualizado()), this, SLOT(actualizarObjeto()));
        break;}
    case TEMA:{
        m_temas = TemasModel::InstanceModel();
        m_objeto->setTable("vistas.themes_alternatives");
        ui->btAnadir->setText("Aña&dir tema");
        connect(m_temas, SIGNAL(actualizado()), this, SLOT(actualizarObjeto()));
        break;}
    default:
        break;
    }

    m_objeto->select();
}

void dlgSeleccionarGeneral::cargarModelo(){

    m_objeto_proxy = new ProxyNombres(tipo_seleccionado, this);
    m_objeto_proxy->setSourceModel(m_objeto);

    ui->twSeleccionar->setModel(m_objeto_proxy);
    ui->twSeleccionar->hideColumn(0);
    ui->twSeleccionar->setAlternatingRowColors(true);
    ui->twSeleccionar->resizeColumnsToContents();
    ui->twSeleccionar->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twSeleccionar->setSelectionMode(QAbstractItemView::SingleSelection);
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
    case CAPITULO:
        capitulo();
    case TEMA:
        tema();
    case DIOCESIS:
        diocesis();
    default:
        break;
    }
}

void dlgSeleccionarGeneral::casa(){
    /*
     * ATENCiÖN: esta nota es antigua: ahora emito una casa, pero pierdo lo de la provincia?
     * bueno, se podría hacer con una signal que emita tb el nombre de la provincia...
     *
     * Nota antigua:
     * en teoría habría que emitir una casa, pero debido a que quiero construir
     * el nombre con la provincia, etc. sería más lío pq en el objeto Casa
     * tengo que poner lugar/provincia/etc. como int y luego tendría que convertirlo
     * en algún sitio a QString... por eso paso por ahora.
     */

    Casa casa;

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

    // esto eran variables anteriores
    /*
    QString lugar = m_objeto->data(m_objeto_proxy->mapToSource(idx2), Qt::DisplayRole).toString();
    QString provincia = m_objeto->data(m_objeto_proxy->mapToSource(idx3), Qt::DisplayRole).toString();
    QString advocacion = m_objeto->data(m_objeto_proxy->mapToSource(idx4), Qt::DisplayRole).toString();
    */

    casa.setId(id);
    casa.setNombre(nombre);

    emit(casaEscogidaSignal(casa));
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
    QModelIndex idx3 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 3);

    if (!idx0.isValid())
        return;

    int id = m_objeto->data(m_objeto_proxy->mapToSource(idx0), Qt::DisplayRole).toInt();
    QString nombre = m_objeto->data(m_objeto_proxy->mapToSource(idx1), Qt::DisplayRole).toString();
    QString apellidos = m_objeto->data(m_objeto_proxy->mapToSource(idx2), Qt::DisplayRole).toString();
    QString origen = m_objeto->data(m_objeto_proxy->mapToSource(idx3), Qt::DisplayRole).toString();

    autor.setId(id);
    autor.setNombre(nombre);
    autor.setApellidos(apellidos);
    autor.setOrigen(origen);

    emit(personaEscogidaSignal(autor));
    close();
}

void dlgSeleccionarGeneral::provincia(){

    Provincia provincia;

    // tiene que haber otra manera de hacer esto...
    QModelIndex idx0 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 0);
    QModelIndex idx1 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 1);

    if (!idx0.isValid())
        return;

    int id = m_objeto->data(m_objeto_proxy->mapToSource(idx0), Qt::DisplayRole).toInt();
    QString nombre = m_objeto->data(m_objeto_proxy->mapToSource(idx1), Qt::DisplayRole).toString();

    provincia.setId(id);
    provincia.setNombre(nombre);

    emit(provinciaEscogidaSignal(provincia));
    close();

}

void dlgSeleccionarGeneral::diocesis(){

    Diocesis diocesis;

    // tiene que haber otra manera de hacer esto...
    QModelIndex idx0 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 0);
    QModelIndex idx1 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 1);

    if (!idx0.isValid())
        return;

    int id = m_objeto->data(m_objeto_proxy->mapToSource(idx0), Qt::DisplayRole).toInt();
    QString nombre = m_objeto->data(m_objeto_proxy->mapToSource(idx1), Qt::DisplayRole).toString();

    diocesis.setId(id);
    diocesis.setNombre(nombre);

    emit(diocesisEscogidaSignal(diocesis));
    close();

}

void dlgSeleccionarGeneral::capitulo(){

    Capitulo capitulo;

    // tiene que haber otra manera de hacer esto...
    QModelIndex idx0 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 0);
    QModelIndex idx1 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 1);
    QModelIndex idx2 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 2); // esto es el año

    if (!idx0.isValid())
        return;

    int id = m_objeto->data(m_objeto_proxy->mapToSource(idx0), Qt::DisplayRole).toInt();
    QString nombre = m_objeto->data(m_objeto_proxy->mapToSource(idx1), Qt::DisplayRole).toString();
    QDate fecha = m_objeto->data(m_objeto_proxy->mapToSource(idx2), Qt::DisplayRole).toDate();

    capitulo.setId(id);
    capitulo.setNombre(nombre);
    capitulo.setFechaInicio(fecha);

    emit(capituloEscogidoSignal(capitulo));
    close();

}

void dlgSeleccionarGeneral::tema(){

    Tema tema;

    // tiene que haber otra manera de hacer esto...
    QModelIndex idx0 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 0);
    QModelIndex idx1 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 1);

    if (!idx0.isValid())
        return;

    int id = m_objeto->data(m_objeto_proxy->mapToSource(idx0), Qt::DisplayRole).toInt();
    QString nombretema = m_objeto->data(m_objeto_proxy->mapToSource(idx1), Qt::DisplayRole).toString();

    tema.setId(id);
    tema.setTema(nombretema);

    emit(temaEscogidoSignal(tema));

    close();

}

void dlgSeleccionarGeneral::anadirObjeto(){

    switch (tipo_seleccionado) {
    case CASA:{
        dlgNuevaCasa *dlgcasa = new dlgNuevaCasa(this);
        dlgcasa->show();
        break;}
    case LUGAR:{
        dlgNuevoLugar *dlglugar = new dlgNuevoLugar(this);
        dlglugar->show();
        break;}
    case PROVINCIA:{
        dlgNuevaProvincia *dlgprovincia = new dlgNuevaProvincia(this);
        dlgprovincia->show();
        break;}
    case PERSONA:{
        dlgNuevaPersona *dlgpersona = new dlgNuevaPersona(this);
        dlgpersona->show();
        break;}
    case CAPITULO:{
        dlgNuevoCapitulo *dlgcapitulo = new dlgNuevoCapitulo(this);
        dlgcapitulo->show();
        break;}
    case DIOCESIS:{
        dlgNuevaDiocesis *dlgdiocesis = new dlgNuevaDiocesis(this);
        dlgdiocesis->show();
        break;}
    case TEMA:{
        anadirTema();
    }
        /*
         * TODO: faltaría añadir diócesis! pero por ahora paso pq en principio
         * no debería darse el caso de que meto la diócesis desde aquí...
         */
    default:
        break;
    }

}

void dlgSeleccionarGeneral::actualizarObjeto(){
    m_objeto->select();
    ui->twSeleccionar->resizeRowsToContents();
}

void dlgSeleccionarGeneral::anadirTema(){
    Tema *tema = new Tema();

    QString tematitulo = QInputDialog::getText(this, "Introduzca nuevo tema", "Nueva tema");

    if (!tematitulo.isEmpty()){
        tema->setTema(tematitulo);

        if (!m_temas->AnadirTema(tema)){
            int ret = QMessageBox::warning(this, "Error al introducir la resolución",
                                           "Error al introducir la resolución en la BD");
            return;
        }
    }
}

void dlgSeleccionarGeneral::comprobarVacio()
{
    if (m_objeto->rowCount() == 0){
        qDebug() << "cerrando...";
        close();
    }
}
