#include "dlgnuevapersona.h"
#include "ui_dlgnuevapersona.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QCompleter>
#include <QMdiSubWindow>
#include <QMessageBox>

#include "models/personasmodel.h"
#include "models/qjsonmodel.h"
#include "gui/dlgdetalles.h"
#include "objs/variados.h"
#include "objs/persona.h"
#include "widgets/myqmdiarea.h"

dlgNuevaPersona::dlgNuevaPersona(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgNuevaPersona)
{
    ui->setupUi(this);

    mdiarea = MyQmdiArea::Instance(this);

    m_personas = PersonasModel::InstanceModel();

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarPersona()));

    nombres_compl = new QCompleter(this);
    apellidos_compl = new QCompleter(this);
    diocesis_compl = new QCompleter(this);
    nombres_query = new QSqlQueryModel(this);
    apellidos_query = new QSqlQueryModel(this);
    diocesis_query = new QSqlQueryModel(this);

    jsongestor = new QJsonModel(this);
    otrosnombres_json = new QJsonModel(this);
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

    diocesis_query->setQuery("SELECT DISTINCT birth_diocesis FROM persons WHERE birth_diocesis IS NOT NULL ORDER BY birth_diocesis");
    diocesis_compl->setModel(diocesis_query);
    diocesis_compl->setCompletionColumn(0);
    diocesis_compl->setCaseSensitivity(Qt::CaseInsensitive);

    ui->txtDiocesis->setCompleter(diocesis_compl);

}

void dlgNuevaPersona::aceptarPersona(){

    Persona *persona = new Persona();

    QString nombre = ui->txtNombre->text();
    QString apellidos = ui->txtApellidos->text();
    QString origen = ui->txtOrigen->text();
    bool buscado = ui->ckBuscado->checkState();
    bool wiki = ui->ckWiki->checkState();
    bool viaf = ui->ckViaf->checkState();
    QString wikilink = ui->txtWiki->text();
    QString viaflink = ui->txtViaf->text();
    QString wikidata = ui->txtWikidata->text();
    QString notas = ui->txtNotas->toPlainText();
    QString nacimiento = ui->txtNacimiento->text();
    QString muerte = ui->txtMuerte->text();
    QString diocesis = ui->txtDiocesis->text();
    bool volveramirar = ui->ckVolverMirar->checkState();
    int cantidadinfo = ui->spCantidadInfo->value();

    QString otrosnombres;

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
    persona->setOrigen(origen);
    persona->setBuscado(buscado);
    persona->setWiki(wiki);
    persona->setViaf(viaf);
    persona->setWikilink(wikilink);
    persona->setViaflink(viaflink);
    persona->setWikidata(wikidata);
    persona->setNacimiento(nacimiento);
    persona->setMuerte(muerte);
    persona->setDiocesis(diocesis);
    persona->setVolverMirar(volveramirar);
    persona->setCantidadInfo(cantidadinfo);
    persona->setOtrosnombres(otrosnombres);
    persona->setNotas(notas);

    if (m_personas->AnadirPersona(persona)){
        //QSqlQuery lastid("select currval('capitulos_capitulo_id_seq')");
        QSqlQuery lastid("select max(person_id) from persons");

        lastid.first();
        int id = lastid.value(0).toInt();
        introducirJson(id);
        borrarCampos();
        cargarCompleters();
        return;
    }
    else{
        int ret = QMessageBox::warning(this, "Error al introducir la resolución",
                                       "Error al introducir la resolución en la BD");
        return;
    }

}

void dlgNuevaPersona::on_btDetalles_clicked()
{
    dlgdetalles = new dlgDetalles(jsongestor, PERSONADETALLES, false, this);
    QMdiSubWindow *window = mdiarea->addSubWindow(dlgdetalles);
    window->show();
}

void dlgNuevaPersona::introducirJson(const int id){

    QSqlQuery query;
    int totaljson;

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

    dlgotrosnombres = new dlgDetalles(otrosnombres_json, OTROS, false, this);
    QMdiSubWindow *window = mdiarea->addSubWindow(dlgotrosnombres);
    window->show();
}

void dlgNuevaPersona::cerrar()
{
    parentWidget()->close();
}

void dlgNuevaPersona::borrarCampos(){

    ui->txtNombre->setText("");
    ui->txtApellidos->setText("");
    ui->txtMuerte->setText("");
    ui->txtNacimiento->setText("");
    ui->txtViaf->setText("");
    ui->txtWiki->setText("");
    ui->txtWikidata->setText("");
    ui->txtNotas->clear();

    ui->ckBuscado->setCheckState(Qt::Unchecked);
    ui->ckViaf->setCheckState(Qt::Unchecked);
    ui->ckWiki->setCheckState(Qt::Unchecked);
    ui->ckVolverMirar->setCheckState(Qt::Unchecked);

    ui->txtNotas->clear();

    /*
     * recargamos/vaciamos las clases json donde guardo
     * diversos tipos de datos.
     * De todas formas: no sé si hay una forma mejor...
     */
    jsongestor = new QJsonModel(this);
    otrosnombres_json = new QJsonModel(this);

    ui->txtNombre->setFocus();
}

