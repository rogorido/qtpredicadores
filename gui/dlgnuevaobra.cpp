#include "dlgnuevaobra.h"
#include "ui_dlgnuevaobra.h"

#include "models/lugaresmodel.h"
#include "dlgseleccionargeneral.h"
#include "dlgnuevolugar.h"
#include "objs/variados.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QInputDialog>
#include <QDebug>

dlgNuevaObra::dlgNuevaObra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaObra)
{
    ui->setupUi(this);

    m_lugares = LugaresModel::InstanceModel();

    connect(ui->btAnadirLugar, SIGNAL(clicked()), this, SLOT(on_btAnadirLugar_clicked()));
    connect(ui->txtLugar, SIGNAL(dobleclick()), this, SLOT(on_btIntroducirLugar_clicked()));
    connect(ui->txtAutor, SIGNAL(dobleclick()), this, SLOT(on_btSeleccionarAutor_clicked()));

    cargarCompleters();
}

dlgNuevaObra::~dlgNuevaObra()
{
    delete ui;
}

void dlgNuevaObra::cargarCompleters(){

    m_lugaresoriginales = new QSqlQueryModel(this);
    m_lugaresoriginales->setQuery("SELECT lugar_impresion_original FROM obras.obras ORDER BY lugar_impresion_original");

    c_lugaresoriginales = new QCompleter(m_lugaresoriginales, this);
    c_lugaresoriginales->setCompletionColumn(0);
    c_lugaresoriginales->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtLugarOriginalImpresion->setCompleter(c_lugaresoriginales);

    m_editores = new QSqlQueryModel(this);
    m_editores->setQuery("SELECT editor FROM obras.obras ORDER BY editor");

    c_editor = new QCompleter(m_editores, this);
    c_editor->setCompletionColumn(0);
    c_editor->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtEditor->setCompleter(c_editor);

    m_idiomas = new QSqlQueryModel(this);
    m_idiomas->setQuery("SELECT idioma FROM obras.obras ORDER BY idioma");

    c_idiomas = new QCompleter(m_idiomas, this);
    c_idiomas->setCompletionColumn(0);
    c_idiomas->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtIdioma->setCompleter(c_idiomas);

}

void dlgNuevaObra::on_btAnadirLugar_clicked(){

    dlgNuevoLugar *dlglugar = new dlgNuevoLugar(this);
    dlglugar->show();
    cargarCompleters();
}

void dlgNuevaObra::on_btSeleccionarAutor_clicked()
{
    dlgSeleccionarGeneral *dlgSeleccionar = new dlgSeleccionarGeneral(PERSONA, this);
    dlgSeleccionar->show();

    connect(dlgSeleccionar, SIGNAL(personaEscogidaSignal(Persona)), this, SLOT(actualizarPersona(Persona)));

}

void dlgNuevaObra::actualizarPersona(Persona autor){

    autorescogido = new Persona();

    autorescogido->setId(autor.getId());
    autorescogido->setNombre(autor.getNombre());
    autorescogido->setApellidos(autor.getApellidos());

    QString nombre = autorescogido->getNombre() + ' ' + autorescogido->getApellidos();

    ui->txtAutor->setText(nombre);

}

void dlgNuevaObra::on_btIntroducirLugar_clicked()
{
    dlgSeleccionarGeneral *dlgSeleccionar = new dlgSeleccionarGeneral(LUGAR, this);
    dlgSeleccionar->show();

    connect(dlgSeleccionar, SIGNAL(lugarEscogidoSignal(Lugar)), this, SLOT(actualizarLugar(Lugar)));
}

void dlgNuevaObra::actualizarLugar(Lugar lugar){

    lugarescogido = new Lugar();

    lugarescogido->setId(lugar.getId());
    lugarescogido->setLugar(lugar.getLugar());

    ui->txtLugar->setText(lugarescogido->getLugar());
}
