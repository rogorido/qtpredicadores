#include "dlgnuevaobra.h"
#include "ui_dlgnuevaobra.h"

#include "models/lugaresmodel.h"
#include "models/obrasmodel.h"
#include "models/qjsonmodel.h"
#include "dlgseleccionargeneral.h"
#include "dlgnuevolugar.h"
#include "objs/obra.h"
#include "objs/variados.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QCompleter>
#include <QInputDialog>
#include <QDebug>
#include <QMessageBox>

dlgNuevaObra::dlgNuevaObra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaObra)
{
    ui->setupUi(this);

    m_lugares = LugaresModel::InstanceModel();
    m_obras = ObrasModel::InstanceModel();

    // lo pasamos como referencia. ver header.
    dlgtemas = new dlgTemas(&temasescogidos, this);

    json_detalles = new QJsonModel(this);
    dlgdetalles = new dlgDetalles(json_detalles, OBRA, this);

    connect(ui->btAnadirLugar, SIGNAL(clicked()), this, SLOT(on_btAnadirLugar_clicked()));
    connect(ui->txtLugar, SIGNAL(dobleclick()), this, SLOT(on_btIntroducirLugar_clicked()));
    connect(ui->txtAutor, SIGNAL(dobleclick()), this, SLOT(on_btSeleccionarAutor_clicked()));
    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(close()));
    // mostramos el form de dlgdetalles que ya está creado...
    connect(ui->btDetalles, SIGNAL(clicked(bool)), dlgdetalles, SLOT(show()));

    cargarCompleters();
}

dlgNuevaObra::~dlgNuevaObra()
{
    delete ui;
}

void dlgNuevaObra::cargarCompleters(){

    m_lugaresoriginales = new QSqlQueryModel(this);
    m_lugaresoriginales->setQuery("SELECT DISTINCT place_print_original FROM works.works ORDER BY place_print_original");

    c_lugaresoriginales = new QCompleter(m_lugaresoriginales, this);
    c_lugaresoriginales->setCompletionColumn(0);
    c_lugaresoriginales->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtLugarOriginalImpresion->setCompleter(c_lugaresoriginales);

    m_editores = new QSqlQueryModel(this);
    m_editores->setQuery("SELECT DISTINCT editor FROM works.works ORDER BY editor");

    c_editor = new QCompleter(m_editores, this);
    c_editor->setCompletionColumn(0);
    c_editor->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtEditor->setCompleter(c_editor);

    m_idiomas = new QSqlQueryModel(this);
    m_idiomas->setQuery("SELECT DISTINCT language_work FROM works.works ORDER BY language_work");

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

    /*
     * en lugar de con Persona lo hago con un struct,
     * pq así sé luego borrarlo... Pero creo q esto es una cutrada.
     */

    autorescogido_struct.id = autor.getId();
    autorescogido_struct.elemento = autor.getNombre() + ' ' + autor.getApellidos();

    ui->txtAutor->setText(autorescogido_struct.elemento);

}

void dlgNuevaObra::on_btQuitarAutor_clicked(){

    autorescogido_struct = elementopareado();
    ui->txtAutor->setText("");

}

void dlgNuevaObra::on_btIntroducirLugar_clicked()
{
    dlgSeleccionarGeneral *dlgSeleccionar = new dlgSeleccionarGeneral(LUGAR, this);
    dlgSeleccionar->show();

    connect(dlgSeleccionar, SIGNAL(lugarEscogidoSignal(Lugar)), this, SLOT(actualizarLugar(Lugar)));
}

void dlgNuevaObra::actualizarLugar(Lugar lugar){

    /*
     * en lugar de con Lugar lo hago con un struct,
     * pq así sé luego borrarlo... Pero creo q esto es una cutrada.
     */

    lugarescogido_struct.id = lugar.getId();
    lugarescogido_struct.elemento = lugar.getLugar();

    ui->txtLugar->setText(lugarescogido_struct.elemento);
}

void dlgNuevaObra::on_btQuitarLugar_clicked(){

    lugarescogido_struct = elementopareado();
    ui->txtLugar->setText("");
}

void dlgNuevaObra::on_btTemas_clicked(){

    dlgtemas->show();

}

void dlgNuevaObra::on_btOK_clicked(){

    Obra *obra = new Obra();

    QString titulo = ui->txtTitulo->toPlainText();
    QString idioma = ui->txtIdioma->text();
    int autor = autorescogido_struct.id;
    QString tipo = ui->txtTipo->text();
    QString formato = ui->txtFormato->text();
    int tomos = ui->spTomos->value();
    QString paginas = ui->txtNumeroPags->text();
    bool impreso = ui->ckImpreso->checkState();
    bool talvez_impreso = ui->ckTalVezImpreso->checkState();
    bool manuscrito = ui->ckManuscrito->checkState();
    QString lugar_impresion_original = ui->txtLugarOriginalImpresion->text();
    QString editor = ui->txtEditor->text();
    int lugar_impresion = lugarescogido_struct.id;
    int fecha = ui->spFechaImpresion->value();
    bool referencias = ui->ckReferencias->checkState();
    bool volveramirar = ui->ckVolverMirar->checkState();
    bool tituloreducido = ui->ckTituloReducido->checkState();
    bool dudoso = ui->ckDudoso->checkState();
    bool contenido = ui->ckContenido->checkState();
    bool expurgable = ui->ckExpurgable->checkState();
    int interesante = ui->spInteresante->value();
    int fiabilidad = ui->spFiabilidad->value();
    bool investigar = ui->ckInvestigar->checkState();
    QString notas = ui->txtNotas->toPlainText();
    QString pagequetif = ui->txtPageQuetif->text();

    qDebug() << "el autor es: " << autor;

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
    obra->setInvestigar(investigar);
    obra->setPageQuetif(pagequetif);
    obra->setNotas(notas);

    if (m_obras->AnadirObra(obra)) {
        QSqlQuery lastid("select max(work_id) from works");

        lastid.first();
        int id = lastid.value(0).toInt();

        introducirTemas(id);
        introducirJson(id);
        borrarCampos();
    }
    else {
        int ret = QMessageBox::warning(this, "Error al introducir la resolución",
                                       "Error al introducir la resolución en la BD");
        return;
    }

}

void dlgNuevaObra::introducirTemas(int id){

    if (temasescogidos.size() == 0)
        return;

    for (int i = 0; i < temasescogidos.size(); ++i) {

        QSqlQuery query;
        query.prepare("INSERT INTO works.works_themes(work_id, theme_id) VALUES (:work, :tema)");
        query.bindValue(":work", id);
        query.bindValue(":tema", temasescogidos.at(i).id);
        query.exec();
    }
}

void dlgNuevaObra::borrarCampos(){

    ui->txtTitulo->setText("");
    ui->txtFormato->setText("");
    ui->txtIdioma->setText("");
    ui->txtLugarOriginalImpresion->setText("");
    ui->txtNumeroPags->setText("");
    ui->txtEditor->setText("");
    ui->txtTipo->setText("");
    ui->txtNotas->setText("");
    ui->txtTraduccion->setText("");
    ui->txtPageQuetif->setText("");

    ui->ckContenido->setCheckState(Qt::Unchecked);
    ui->ckDudoso->setCheckState(Qt::Unchecked);
    ui->ckExpurgable->setCheckState(Qt::Unchecked);
    ui->ckImpreso->setCheckState(Qt::Unchecked);
    ui->ckManuscrito->setCheckState(Qt::Unchecked);
    ui->ckVolverMirar->setCheckState(Qt::Unchecked);
    ui->ckTalVezImpreso->setCheckState(Qt::Unchecked);

    ui->spFechaImpresion->setValue(1400);
    ui->spTomos->setValue(0);
    ui->spInteresante->setValue(50);
    ui->spFiabilidad->setValue(50);

    /*
     * vaciamos lo de los temas y lo de lugar pero no lo del autor
     * pq así podemos meter varios libros del mismo auto.
     */
    temasescogidos.clear();
    dlgtemas = new dlgTemas(&temasescogidos, this);

    ui->txtLugar->setText("");
    lugarescogido_struct = elementopareado();

    ui->txtTitulo->setFocus();
}


void dlgNuevaObra::introducirJson(const int id){

    QSqlQuery query;
    int totaljson;

    totaljson = json_detalles->getSize();

    if (totaljson == 0)
        return;

    for (int var = 0; var < totaljson; ++var) {

        QString jsonfinal = json_detalles->getJsonString(var);

        query.prepare("INSERT INTO works_details(work_id, details) VALUES(:workid, :json)");
        query.bindValue(":workid", id);
        query.bindValue(":json", jsonfinal);
        query.exec();
    }
}
