#include "dlgnuevacasa.h"
#include "ui_dlgnuevacasa.h"

#include <QSqlRecord>
#include <QInputDialog>
#include <QCompleter>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMdiSubWindow>
#include <QMessageBox>

#include "models/lugaresmodel.h"
#include "models/casasmodel.h"
#include "models/provinciasmodel.h"
#include "objs/casa.h"
#include "objs/variados.h"
#include "gui/dlgseleccionargeneral.h"
#include "gui/dlgfuenteentrada.h"
#include "widgets/myqmdiarea.h"

dlgNuevaCasa::dlgNuevaCasa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgNuevaCasa)
{
    ui->setupUi(this);

    mdiarea = MyQmdiArea::Instance(this);

    fuentedatos = new QJsonObject();

    m_lugares = LugaresModel::InstanceModel();
    m_casas = CasasModel::InstanceModel();

    ui->txtProvincia->setClearButtonEnabled(true);
    ui->txtLugar->setClearButtonEnabled(true);

    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(cerrar()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarCasa()));
    connect(ui->txtLugar, SIGNAL(dobleclick()), this, SLOT(anadirLugar()));
    connect(ui->btQuitarLugar, SIGNAL(clicked()), this, SLOT(quitarLugar()));
    connect(ui->txtProvincia, SIGNAL(dobleclick()), this, SLOT(anadirProvincia()));
    connect(ui->btFuente, SIGNAL(clicked(bool)), this, SLOT(anadirFuente()));

    cargarModelos();

}

dlgNuevaCasa::~dlgNuevaCasa()
{
    delete ui;
}

void dlgNuevaCasa::aceptarCasa(){

    Casa *casa = new Casa();

    QString nombre = ui->txtNombre->text();
    int lugar;
    int provincia;
    bool buscado = ui->ckBuscado->checkState();
    bool masculino = ui->ckMasculino->checkState();
    bool wiki = ui->ckWiki->checkState();
    QString tipo = ui->txtTipo->text();
    QString advocacion = ui->txtAdvocacion->text();
    QString diocesis = ui->txtDiocesis->text();
    // este  sería interesante hacerlo con QJson...
    //QString otrosnombres;
    bool quetif = ui->ckQuetif->checkState();
    QString fechafundacion = ui->txtFechaFundacion->text();
    QString fechaeliminacion = ui->txtEliminada->text();
    QString notas = ui->txtNotas->toPlainText();
    bool studiumgenerale = ui->ckStudium->checkState();
    QString otrosdatos; // aquí va el json de la fuente

    /*
     * hay que comprobar que esté vacío?
     * entiendo q un struct no se puede comprobar... además de que
     * vacío no puede estar pq lo inicializo. Comprobamos que no sea 0
     * abajo al meterlo en la clase Casa.
     */
    lugar = lugar_struct.id;
    provincia = provincia_struct.id;

    if (fuente_recibida) {
        /*
         * ATENCIÓn: aquí lo que hago es dereferenciar un pointer,
         * porque QJsonDocument me pide una referencia y fuentedatos
         * es un pointer...
         */
        QJsonDocument jsondoc(*fuentedatos);
        otrosdatos = jsondoc.toJson(QJsonDocument::Compact);
    }
    else {
        otrosdatos = "";
    }

    casa->setNombre(nombre);
    if (lugar != 0)
        casa->setLugar(lugar);
    if (provincia != 0)
        casa->setProvincia(provincia);
    casa->setBuscado(buscado);
    casa->setWiki(wiki);
    casa->setTipo(tipo);
    casa->setAdvocacion(advocacion);
    casa->setDiocesis(diocesis);
    casa->setQuetif(quetif);
    casa->setMasculino(masculino);
    casa->setFechaFundacion(fechafundacion);
    casa->setFechaEliminacion(fechaeliminacion);
    casa->setNotas(notas);
    casa->setStudiumgenerale(studiumgenerale);

    if (m_casas->AnadirCasa(casa)) {
        borrarCampos();
    }
    else {
        int ret = QMessageBox::warning(this, "Error al introducir la casa",
                                       "Error al introducir la casa en la BD");
        Q_UNUSED(ret)
        return;
    }
}

void dlgNuevaCasa::anadirLugar(){

    dlgSeleccionarGeneral *dlgSeleccionar = new dlgSeleccionarGeneral(LUGAR, this);
    connect(dlgSeleccionar, SIGNAL(lugarEscogidoSignal(Lugar)), this, SLOT(recibirLugar(Lugar)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgSeleccionar);
    window->show();
}

void dlgNuevaCasa::recibirLugar(Lugar lugarescogido){

    lugar_struct.id = lugarescogido.getId();
    lugar_struct.elemento = lugarescogido.getLugar();

    ui->txtLugar->setText(lugar_struct.elemento);

}

void dlgNuevaCasa::anadirFuente()
{
    dlgFuenteEntrada *dlgfuente = new dlgFuenteEntrada(this);
    connect(dlgfuente, SIGNAL(signalFuente(fuente)), this, SLOT(recibirFuente(fuente)));

    dlgfuente->show();
}

void dlgNuevaCasa::quitarLugar(){

    lugar_struct = elementopareado();
}

void dlgNuevaCasa::anadirProvincia(){
    dlgSeleccionarGeneral *dlgSeleccionar = new dlgSeleccionarGeneral(PROVINCIA, this);
    connect(dlgSeleccionar, SIGNAL(provinciaEscogidaSignal(Provincia)), this, SLOT(recibirProvincia(Provincia)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgSeleccionar);
    window->show();
}

void dlgNuevaCasa::recibirProvincia(Provincia provincia){

    provincia_struct.id = provincia.getId();
    provincia_struct.elemento = provincia.getNombre();

    ui->txtProvincia->setText(provincia_struct.elemento);
}

void dlgNuevaCasa::recibirFuente(fuente f)
{
    fuente_recibida = true;

    fuentedatos->insert("book", QJsonValue(f.titulo));
    fuentedatos->insert("volume", f.tomo);
    fuentedatos->insert("pages", f.paginas);
}

void dlgNuevaCasa::cerrar()
{
    this->parentWidget()->close();
}

void dlgNuevaCasa::quitarProvincia(){

    provincia_struct = elementopareado();
    ui->txtProvincia->setText("");
}

void dlgNuevaCasa::borrarCampos(){

    ui->txtNombre->setText("");
    ui->txtLugar->setText("");
    ui->txtLugarOriginario->setText("");
    ui->txtProvincia->setText("");
    ui->txtTipo->setText("");
    ui->txtAdvocacion->setText("");
    ui->txtDiocesis->setText("");
    ui->txtFechaFundacion->setText("");
    ui->txtEliminada->setText("");
    ui->txtNotas->clear();

    ui->ckBuscado->setCheckState(Qt::Unchecked);
    ui->ckMasculino->setCheckState(Qt::Unchecked);
    ui->ckStudium->setCheckState(Qt::Unchecked);
    ui->ckWiki->setCheckState(Qt::Unchecked);

    lugar_struct = elementopareado();
    provincia_struct = elementopareado();

    ui->txtNombre->setFocus();
}

void dlgNuevaCasa::cargarModelos(){

    m_tipos = new QSqlQueryModel(this);
    m_tipos_completer = new QCompleter(this);

    m_tipos->setQuery("SELECT DISTINCT type_house FROM general.houses ORDER BY type_house");
    m_tipos_completer->setModel(m_tipos);
    m_tipos_completer->setCompletionColumn(0);
    m_tipos_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtTipo->setCompleter(m_tipos_completer);

    m_advocaciones = new QSqlQueryModel(this);
    m_advocaciones_completer = new QCompleter(this);

    m_advocaciones->setQuery("SELECT DISTINCT advocation FROM general.houses ORDER BY advocation");
    m_advocaciones_completer->setModel(m_advocaciones);
    m_advocaciones_completer->setCompletionColumn(0);
    m_advocaciones_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtAdvocacion->setCompleter(m_advocaciones_completer);

    m_diocesis = new QSqlQueryModel(this);
    m_diocesis_completer = new QCompleter(this);

    m_diocesis->setQuery("SELECT DISTINCT diocese FROM general.houses ORDER BY diocese");
    m_diocesis_completer->setModel(m_diocesis);
    m_diocesis_completer->setCompletionColumn(0);
    m_diocesis_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtDiocesis->setCompleter(m_diocesis_completer);
}
