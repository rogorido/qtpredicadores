#include "dlgnuevaobra.h"
#include "ui_dlgnuevaobra.h"

#include "lugaresmodel.h"
#include "dlgseleccionarpersona.h"
#include "dlgseleccionarlugar.h"

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
    QString lugar;

    lugar = QInputDialog::getText(this, "Introduzca un nuevo lugar", "Lugar (nombre,país) ");

    if (!lugar.isEmpty()){
        m_lugares->AnadirLugar(lugar);
        cargarCompleters();
    }
}

void dlgNuevaObra::on_pushButton_clicked()
{
    dlgSeleccionarPersona *seleccionarpersona = new dlgSeleccionarPersona(this);
    seleccionarpersona->show();

    connect(seleccionarpersona, SIGNAL(personaEscogida(Persona)), this, SLOT(actualizarPersona(Persona)));

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
    dlgSeleccionarLugar *seleccionarlugar = new dlgSeleccionarLugar(this);
    seleccionarlugar->show();

    connect(seleccionarlugar, SIGNAL(lugarEscogido(Lugar)), this, SLOT(actualizarLugar(Lugar)));
}

void dlgNuevaObra::actualizarLugar(Lugar lugar){

    lugarescogido = new Lugar();

    lugarescogido->setId(lugar.getId());
    lugarescogido->setLugar(lugar.getLugar());

    ui->txtLugar->setText(lugarescogido->getLugar());
}
