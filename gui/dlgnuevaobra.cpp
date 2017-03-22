#include "dlgnuevaobra.h"
#include "ui_dlgnuevaobra.h"

#include "models/lugaresmodel.h"
#include "dlgseleccionargeneral.h"
#include "dlgnuevolugar.h"
#include "objs/obra.h"
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
    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(close()));

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

void dlgNuevaObra::on_btOK_clicked(){

    Obra *obra = new Obra();

    QString titulo = ui->txtTitulo->toPlainText();
    QString idioma = ui->txtIdioma->text();
    int autor = autorescogido->getId();
    QString tipo = ui->txtTipo->text();
    QString formato = ui->txtFormato->text();
    int tomos = ui->spTomos->value();
    QString paginas = ui->txtNumeroPags->text();
    bool impreso = ui->ckImpreso->checkState();
    bool talvez_impreso = ui->ckTalVezImpreso->checkState();
    bool manuscrito = ui->ckManuscrito->checkState();
    QString lugar_impresion_original = ui->txtLugarOriginalImpresion->text();
    QString editor = ui->txtEditor->text();
    int lugar_impresion = lugarescogido->getId();
    int fecha = ui->spFechaImpresion->value();
    bool referencias = ui->ckReferencias->checkState();
    bool volveramirar = ui->ckVolverMirar->checkState();
    bool tituloreducido = ui->ckTituloReducido->checkState();
    bool dudoso = ui->ckDudoso->checkState();
    bool contenido = ui->ckContenido->checkState();
    bool expurgable = ui->ckExpurgable->checkState();
    int interesante = ui->spInteresante->value();
    int fiabilidad = ui->spFiabilidad->value();
    QString notas = ui->txtNotas->toPlainText();

    obra->setTitulo(titulo);
    obra->setIdioma(idioma);
    obra->setAutor(autor);
    obra->setTipo(tipo);
    obra->setFormato(formato);
    obra->setTomos(tomos);
    obra->setNumeroPags(paginas);
    obra->setImpreso(impreso);
    obra->setTalVezImpreso(talvez_impreso);
    obra->setManuscrito(manuscrito);
    obra->setLugar(lugar_impresion);
    obra->setLugarOriginal(lugar_impresion_original);
    obra->setEditor(editor);
    obra->setFecha(fecha);
    obra->setReferencias(referencias);
    obra->setVolverMirar(volveramirar);
    obra->setExpurgable(expurgable);
    obra->setDudoso(dudoso);
    obra->setContenido(contenido);
    obra->setTituloReducido(tituloreducido);
    obra->setInteresante(interesante);
    obra->setFiabilidad(fiabilidad);
    obra->setNotas(notas);

}
