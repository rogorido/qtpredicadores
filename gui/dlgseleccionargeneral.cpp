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
#include "gui/dlgobispos.h"

#include "widgets/myqmdiarea.h"
#include "widgets/fechasdelegate.h"

#include <QInputDialog>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QMdiSubWindow>
#include <QModelIndex>
#include <QMenu>
#include <QAction>
#include <QDebug>

dlgSeleccionarGeneral::dlgSeleccionarGeneral(tiposeleccionar valor, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgSeleccionarGeneral), tipo_seleccionado(valor)
{
    ui->setupUi(this);

    mdiarea = MyQmdiArea::Instance(this);

    ui->txtFiltro->setClearButtonEnabled(true);

    cargarTipo();
    cargarModelo();
    cargarTituloVentana();
    cargarMenus();

    ui->twSeleccionar->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->twSeleccionar->setAutoScroll(false);
    ui->twSeleccionar->verticalHeader()->hide();

    connect(ui->btAnadir, SIGNAL(clicked(bool)), this, SLOT(anadirObjeto()));
    connect(ui->txtFiltro, SIGNAL(textEdited(QString)), this, SLOT(actualizarFiltro(QString)));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->twSeleccionar, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(aceptar()));
    connect(ui->twSeleccionar, SIGNAL(clicked(const QModelIndex &)), this, SLOT(seleccionarObjeto(QModelIndex)));
    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    connect(ui->twSeleccionar, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(menuContextual(const QPoint &)));

    ui->txtFiltro->setFocus();
}

dlgSeleccionarGeneral::~dlgSeleccionarGeneral()
{
    delete ui;
}

void dlgSeleccionarGeneral::cargarTipo(){
    m_objeto = new QSqlQueryModel(this);

    switch (tipo_seleccionado) {
    case CASA:{
        m_casas = CasasModel::InstanceModel();
        m_objeto = m_casas;
        ui->btAnadir->setText("Aña&dir casa");
        connect(m_casas, SIGNAL(actualizado()), this, SLOT(actualizarObjeto()));
        ui->btVerObjeto->hide();
        break;}
    case LUGAR:{
        m_lugares = LugaresModel::InstanceModel();
        sql_general = "SELECT * FROM vistas.places_alternatives";
        ui->btAnadir->setText("Aña&dir lugar");
        connect(m_lugares, SIGNAL(actualizado()), this, SLOT(actualizarObjeto()));
        ui->btVerObjeto->hide();
        break;}
    case PROVINCIA:{
        m_provincias = ProvinciasModel::InstanceModel();
        sql_general = "SELECT * FROM vistas.provinces_alternatives";
        ui->btAnadir->setText("Aña&dir provincia");
        connect(m_provincias, SIGNAL(actualizado()), this, SLOT(actualizarObjeto()));
        ui->btVerObjeto->hide();
        break;}
    case PERSONA:{
        m_personas = PersonasModel::InstanceModel();
        sql_general = "SELECT * FROM vistas.persons_alternatives";
        ui->btAnadir->setText("Aña&dir persona");
        connect(m_personas, SIGNAL(actualizado()), this, SLOT(actualizarObjeto()));

        // lo de ver la persona
        ui->btVerObjeto->show();
        ui->btVerObjeto->setEnabled(true);
        ui->btVerObjeto->setText("Ver persona");

        break;}
    case CAPITULO:{
        m_capitulos = CapitulosModel::InstanceModel();
        sql_general = "SELECT * FROM vistas.chapters_alternatives";
        ui->btAnadir->setText("Aña&dir capítulo");
        connect(m_capitulos, SIGNAL(actualizado()), this, SLOT(actualizarObjeto()));
        ui->btVerObjeto->hide();
        break;}
    case DIOCESIS:{
        m_diocesis = DiocesisModel::InstanceModel();
        sql_general = "SELECT * FROM vistas.dioceses_alternatives";
        comprobarVacio();
        ui->btAnadir->setText("Aña&dir diócesis");
        connect(m_diocesis, SIGNAL(actualizado()), this, SLOT(actualizarObjeto()));
        ui->btVerObjeto->hide();
        break;}
    case TEMA:{
        m_temas = TemasModel::InstanceModel();
        sql_general = "SELECT * FROM vistas.themes_alternatives";
        ui->btAnadir->setText("Aña&dir tema");
        connect(m_temas, SIGNAL(actualizado()), this, SLOT(actualizarObjeto()));
        ui->btVerObjeto->hide();
        break;}
    default:
        break;
    }

    //m_objeto->setQuery(sql_general);
}

void dlgSeleccionarGeneral::cargarTituloVentana()
{
    switch (tipo_seleccionado) {
    case CASA:
        setWindowTitle("Seleccionar casas");
        break;
    case LUGAR:
        setWindowTitle("Seleccionar lugares");
        break;
    case PROVINCIA:
        setWindowTitle("Seleccionar provincia");
        break;
    case PERSONA:
        setWindowTitle("Seleccionar persona");
        break;
    case CAPITULO:
        setWindowTitle("Seleccionar capítulo");
        break;
    case TEMA:
        setWindowTitle("Seleccionar tema");
        break;
    case DIOCESIS:
        setWindowTitle("Seleccionar diócesis");
        break;
    default:
        break;
    }
}

void dlgSeleccionarGeneral::cargarMenus()
{
     menuContexto = new QMenu(this);

     a_verDiocesisPersona = new QAction("Ver diócesis", this);
     connect(a_verDiocesisPersona, SIGNAL(triggered(bool)), this, SLOT(verDiocesisPersona()));

     menuContexto->addAction(a_verDiocesisPersona);

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

    if (tipo_seleccionado == CAPITULO)
        ui->twSeleccionar->setItemDelegateForColumn(2, new FechasDelegate(FechasDelegate::TipoFecha::ONLY_YEAR, this));

    // esto es para modificar el objeto
    switch (tipo_seleccionado) {
    case PERSONA: {
        connect(ui->btVerObjeto, SIGNAL(clicked()), this, SLOT(verObjeto()));
        break;
    }
    default:
        break;
    }
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

void dlgSeleccionarGeneral::menuContextual(const QPoint &point)
{
    qDebug() << "estamos en el menú";

    menuContexto->popup(ui->twSeleccionar->viewport()->mapToGlobal(point));
}

void dlgSeleccionarGeneral::seleccionarObjeto(const QModelIndex &idx)
{
    /*
     * sacamos el índice de la columna 0 que es donde está
     * la id de la resolución, para luego convertirla en int
     * y usarla en el filtro del otro modelo.
     */
    QModelIndex indice = idx.model()->index(idx.row(), 0);
    if (!indice.isValid())
        return;

    QModelIndex indice_verdadero = m_objeto_proxy->mapToSource(indice);

    persona_id = m_objeto->data(indice_verdadero, Qt::DisplayRole).toInt();
}

void dlgSeleccionarGeneral::aceptar(){

    // esto es un poco absurdo, tiene que haber otra manera...
    switch (tipo_seleccionado) {
    case CASA:
        casa();
        break;
    case LUGAR:
        lugar();
        break;
    case PROVINCIA:
        provincia();
        break;
    case PERSONA:
        persona();
        break;
    case CAPITULO:
        capitulo();
        break;
    case TEMA:
        tema();
        break;
    case DIOCESIS:
        diocesis();
        break;
    default:
        break;
    }

    cerrar();
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
}

void dlgSeleccionarGeneral::anadirObjeto(){

    switch (tipo_seleccionado) {
    case CASA:{
        dlgNuevaCasa *dlgcasa = new dlgNuevaCasa(this);
        QMdiSubWindow *window = mdiarea->addSubWindow(dlgcasa);
        window->show();
        break;}
    case LUGAR:{
        dlgNuevoLugar *dlglugar = new dlgNuevoLugar(this);
        QMdiSubWindow *window = mdiarea->addSubWindow(dlglugar);
        window->show();
        break;}
    case PROVINCIA:{
        dlgNuevaProvincia *dlgprovincia = new dlgNuevaProvincia(this);
        QMdiSubWindow *window = mdiarea->addSubWindow(dlgprovincia);
        window->show();
        break;}
    case PERSONA:{
        dlgNuevaPersona *dlgpersona = new dlgNuevaPersona(this);
        QMdiSubWindow *window = mdiarea->addSubWindow(dlgpersona);
        window->show();
        break;}
    case CAPITULO:{
        dlgNuevoCapitulo *dlgcapitulo = new dlgNuevoCapitulo(this);
        QMdiSubWindow *window = mdiarea->addSubWindow(dlgcapitulo);
        window->show();
        break;}
    case DIOCESIS:{
        dlgNuevaDiocesis *dlgdiocesis = new dlgNuevaDiocesis(this);
        QMdiSubWindow *window = mdiarea->addSubWindow(dlgdiocesis);
        window->show();
        break;}
    case TEMA:{
        anadirTema();
        break;
    }
    default:
        break;
    }

}

void dlgSeleccionarGeneral::actualizarObjeto(){

    m_objeto->setQuery(sql_general);
    ui->twSeleccionar->resizeRowsToContents();
}

void dlgSeleccionarGeneral::verObjeto()
{
    /*
     * TODO: esto por ahora solo vale para personas
     */
    QModelIndex indice = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 0);
    if (!indice.isValid())
        return;

    int id = m_objeto->data(m_objeto_proxy->mapToSource(indice), Qt::DisplayRole).toInt();
    qDebug() << "escogido: " << id;

    dlgNuevaPersona *dlgPersonaAModificar = new dlgNuevaPersona(this, id);
    QMdiSubWindow *window = mdiarea->addSubWindow(dlgPersonaAModificar);
    window->show();
}

void dlgSeleccionarGeneral::verDiocesisPersona()
{
    if (persona_id == 0)
        return;

    dlgObispos *dlgobispos = new dlgObispos(this);
    QMdiSubWindow *window = mdiarea->addSubWindow(dlgobispos);
    dlgobispos->seleccionarPersona(persona_id);
    window->show();

}

void dlgSeleccionarGeneral::cerrar()
{
    parentWidget()->close();
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
