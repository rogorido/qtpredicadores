#include "dlgnuevacasa.h"
#include "ui_dlgnuevacasa.h"

#include <QSqlRecord>
#include <QInputDialog>
#include <QCompleter>
#include <QMessageBox>

#include "models/lugaresmodel.h"
#include "models/casasmodel.h"
#include "models/provinciasmodel.h"
#include "objs/casa.h"
#include "objs/variados.h"
#include "gui/dlgseleccionargeneral.h"

dlgNuevaCasa::dlgNuevaCasa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaCasa)
{
    ui->setupUi(this);

    m_lugares = LugaresModel::InstanceModel();
    m_casas = CasasModel::InstanceModel();

    ui->txtProvincia->setClearButtonEnabled(true);
    ui->txtLugar->setClearButtonEnabled(true);

    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarCasa()));
    connect(ui->txtLugar, SIGNAL(dobleclick()), this, SLOT(anadirLugar()));
    connect(ui->btQuitarLugar, SIGNAL(clicked()), this, SLOT(quitarLugar()));
    connect(ui->txtProvincia, SIGNAL(dobleclick()), this, SLOT(anadirProvincia()));

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
    bool wiki = ui->ckWiki->checkState();
    QString tipo = ui->txtTipo->text();
    QString advocacion = ui->txtAdvocacion->text();
    QString diocesis = ui->txtDiocesis->text();
    // este  sería interesante hacerlo con QJson...
    //QString otrosnombres;
    QString notas = ui->txtNotas->toPlainText();
    bool studiumgenerale = ui->ckStudium->checkState();

    // TODO: hay que comprobar que esté vacío?
    lugar = lugar_struct.id;
    provincia = provincia_struct.id;

    casa->setNombre(nombre);
    casa->setLugar(lugar);
    casa->setProvincia(provincia);
    casa->setBuscado(buscado);
    casa->setWiki(wiki);
    casa->setTipo(tipo);
    casa->setAdvocacion(advocacion);
    casa->setDiocesis(diocesis);
    casa->setNotas(notas);
    casa->setStudiumgenerale(studiumgenerale);

    if (m_casas->AnadirCasa(casa)) {
        borrarCampos();
    }
    else {
        int ret = QMessageBox::warning(this, "Error al introducir la casa",
                                       "Error al introducir la casa en la BD");
        return;
    }
}

void dlgNuevaCasa::anadirLugar(){

    dlgSeleccionarGeneral *dlgSeleccionar = new dlgSeleccionarGeneral(LUGAR, this);
    dlgSeleccionar->show();

    connect(dlgSeleccionar, SIGNAL(lugarEscogidoSignal(Lugar)), this, SLOT(recibirLugar(Lugar)));
}

void dlgNuevaCasa::recibirLugar(Lugar lugarescogido){

    lugar_struct.id = lugarescogido.getId();
    lugar_struct.elemento = lugarescogido.getLugar();

    ui->txtLugar->setText(lugar_struct.elemento);

}

void dlgNuevaCasa::quitarLugar(){

    lugar_struct = elementopareado();
}

void dlgNuevaCasa::anadirProvincia(){
    dlgSeleccionarGeneral *dlgSeleccionar = new dlgSeleccionarGeneral(PROVINCIA, this);
    dlgSeleccionar->show();

    connect(dlgSeleccionar, SIGNAL(provinciaEscogidaSignal(Provincia)), this, SLOT(recibirProvincia(Provincia)));
}

void dlgNuevaCasa::recibirProvincia(Provincia provincia){

    provincia_struct.id = provincia.getId();
    provincia_struct.elemento = provincia.getNombre();

    ui->txtProvincia->setText(provincia_struct.elemento);
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
    ui->txtTipo->setCompleter(m_tipos_completer);

    m_advocaciones = new QSqlQueryModel(this);
    m_advocaciones_completer = new QCompleter(this);

    m_advocaciones->setQuery("SELECT DISTINCT advocation FROM general.houses ORDER BY advocation");
    m_advocaciones_completer->setModel(m_advocaciones);
    m_advocaciones_completer->setCompletionColumn(0);
    ui->txtAdvocacion->setCompleter(m_advocaciones_completer);

    m_diocesis = new QSqlQueryModel(this);
    m_diocesis_completer = new QCompleter(this);

    m_diocesis->setQuery("SELECT DISTINCT diocese FROM general.houses ORDER BY diocese");
    m_diocesis_completer->setModel(m_diocesis);
    m_diocesis_completer->setCompletionColumn(0);
    ui->txtDiocesis->setCompleter(m_diocesis_completer);
}
