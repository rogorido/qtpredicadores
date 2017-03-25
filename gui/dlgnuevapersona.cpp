#include "dlgnuevapersona.h"
#include "ui_dlgnuevapersona.h"

#include <QDebug>
#include <QSqlQuery>

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

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarPersona()));

}

dlgNuevaPersona::~dlgNuevaPersona()
{
    delete ui;
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
    // falta lo de los dos json

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
