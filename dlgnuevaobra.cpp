#include "dlgnuevaobra.h"
#include "ui_dlgnuevaobra.h"

#include "lugaresmodel.h"
#include "dlgseleccionarpersona.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QInputDialog>

dlgNuevaObra::dlgNuevaObra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaObra)
{
    ui->setupUi(this);

    m_lugares = LugaresModel::InstanceModel();

    connect(ui->btAnadirLugar, SIGNAL(clicked()), this, SLOT(on_btAnadirLugar_clicked()));

    cargarCompleters();
    cargarCombos();
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

void dlgNuevaObra::cargarCombos(){

    ui->cbLugarImpresion->setModel(m_lugares);
    ui->cbLugarImpresion->setCurrentIndex(-1);
    ui->cbLugarImpresion->setModelColumn(1);

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

    connect(seleccionarpersona, SIGNAL(personaEscogida(AutorStruct)), this, SLOT(actualizarPersona(AutorStruct)));

}

void dlgNuevaObra::actualizarPersona(AutorStruct autor){
    ui->txtAutor->setText(autor.nombre);
    // atención: hace falta meter esos datos en un puntero
    // sobre todo por el id; que luego hay que añadir en la query...
}
