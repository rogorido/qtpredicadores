#include "dlgnuevapersona.h"
#include "ui_dlgnuevapersona.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QCompleter>

#include "objs/persona.h"
#include "models/personasmodel.h"
#include "objs/jsongestor.h"
#include "gui/dlgdetalles.h"

dlgNuevaPersona::dlgNuevaPersona(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaPersona)
{
    ui->setupUi(this);

    m_personas = PersonasModel::InstanceModel();

    jsongestor = new JsonGestor(this);
    dlgdetalles = new dlgDetalles(jsongestor, this);

    otrosnombres_json = new JsonGestor(this);
    dlgotrosnombres = new dlgDetalles(otrosnombres_json, this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarPersona()));

    nombres_compl = new QCompleter(this);
    apellidos_compl = new QCompleter(this);
    nombres_query = new QSqlQueryModel(this);
    apellidos_query = new QSqlQueryModel(this);

    cargarCompleters();

}

dlgNuevaPersona::~dlgNuevaPersona()
{
    delete ui;
}

void dlgNuevaPersona::cargarCompleters(){

    nombres_query->setQuery("SELECT DISTINCT name FROM persons WHERE name IS NOT NULL ORDER BY name");
    nombres_compl->setModel(nombres_query);
    nombres_compl->setCompletionColumn(0);
    nombres_compl->setCaseSensitivity(Qt::CaseInsensitive);

    ui->txtNombre->setCompleter(nombres_compl);

    apellidos_query->setQuery("SELECT DISTINCT family_name FROM persons WHERE family_name IS NOT NULL ORDER BY family_name");
    apellidos_compl->setModel(apellidos_query);
    apellidos_compl->setCompletionColumn(0);
    apellidos_compl->setCaseSensitivity(Qt::CaseInsensitive);

    ui->txtApellidos->setCompleter(apellidos_compl);

}

void dlgNuevaPersona::aceptarPersona(){

    Persona *persona = new Persona();

    QString nombre = ui->txtNombre->text();
    QString apellidos = ui->txtApellidos->text();
    bool buscado = ui->ckBuscado->checkState();
    bool wiki = ui->ckWiki->checkState();
    bool viaf = ui->ckViaf->checkState();
    QString wikilink = ui->txtWiki->text();
    QString viaflink = ui->txtViaf->text();
    QString wikidata = ui->txtWikidata->text();
    QString notas = ui->txtNotas->toPlainText();
    QString nacimiento = ui->txtNacimiento->text();
    QString muerte = ui->txtMuerte->text();
    bool volveramirar = ui->ckVolverMirar->checkState();
    int cantidadinfo = ui->spCantidadInfo->value();

    QString otrosnombres;

    otrosnombres_json->actualizarPrevioIntroducir();

    // entiendo q solo hay un qvector en este otrosnombres_json, no?
    if (otrosnombres_json->getSize() > 0) {
        qDebug() << "estamos aquí";
        otrosnombres = otrosnombres_json->getJsonString(0);
    }
    else
        otrosnombres = "";

    qDebug() << "los otros nombres son: " << otrosnombres;

    persona->setNombre(nombre);
    persona->setApellidos(apellidos);
    persona->setBuscado(buscado);
    persona->setWiki(wiki);
    persona->setViaf(viaf);
    persona->setWikilink(wikilink);
    persona->setViaflink(viaflink);
    persona->setWikidata(wikidata);
    persona->setNacimiento(nacimiento);
    persona->setMuerte(muerte);
    persona->setVolverMirar(volveramirar);
    persona->setCantidadInfo(cantidadinfo);
    persona->setOtrosnombres(otrosnombres);
    persona->setNotas(notas);

    m_personas->AnadirPersona(persona);

    // Aquí el problema es que no comprobamos que la query hay sido existosa...

    //QSqlQuery lastid("select currval('capitulos_capitulo_id_seq')");
    QSqlQuery lastid("select max(person_id) from persons");

      lastid.first();
      int id = lastid.value(0).toInt();

      qDebug() << "El valor de la persona es: " << id;

      introducirJson(id);

}

void dlgNuevaPersona::on_btDetalles_clicked()
{
    dlgdetalles->show();
}

void dlgNuevaPersona::introducirJson(const int id){

    QSqlQuery query;
    int totaljson;

    jsongestor->actualizarPrevioIntroducir();
    totaljson = jsongestor->getSize();

    if (totaljson == 0)
        return;

    for (int var = 0; var < totaljson; ++var) {

        QString jsonfinal = jsongestor->getJsonString(var);

        query.prepare("INSERT INTO persons_details(person_id, details) VALUES(:personid, :json)");
        query.bindValue(":personid", id);
        query.bindValue(":json", jsonfinal);
        query.exec();
    }
}

void dlgNuevaPersona::on_btOtrosNombres_clicked(){

    dlgotrosnombres->show();

}

