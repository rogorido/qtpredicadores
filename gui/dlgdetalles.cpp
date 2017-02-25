#include "dlgdetalles.h"
#include "ui_dlgdetalles.h"

#include "objs/jsongestor.h"
#include "dlgseleccionarpersona.h"
#include "dlgseleccionarlugar.h"

#include <QSqlQueryModel>
#include <QCompleter>

dlgDetalles::dlgDetalles(JsonGestor *json, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgDetalles), jsondetalles(json)
{
    ui->setupUi(this);
    jsondetalles->setTreeWidget(ui->twDetalles);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(hide()));
    connect(ui->btNuevoBloque, SIGNAL(clicked(bool)), jsondetalles, SLOT(nuevoBloqueJson()));
    connect(ui->txtKey, SIGNAL(editingFinished()), this, SLOT(actualizarCompleterValues()));

    cargarModelos();
}

dlgDetalles::~dlgDetalles()
{
    delete ui;
}

void dlgDetalles::recibirPersona(Persona persona){
    int id = persona.getId();
    QString valor = persona.getNombre() + ' ' + persona.getApellidos();

    jsondetalles->anadirValor("Persona", valor, id);
}

void dlgDetalles::recibirLugar(Lugar lugar){
    int id = lugar.getId();
    QString valor = lugar.getLugar();

    jsondetalles->anadirValor("Lugar", valor, id);
}

void dlgDetalles::actualizarCompleterValues(){
    QString key;

    key = ui->txtKey->text();

    if (!key.isEmpty())
        m_values->setQuery(QString("SELECT DISTINCT value from resoluciones_detalles, json_each_text(detalle) "
                               "WHERE key='%1' ORDER BY value;").arg(key));

}

void dlgDetalles::on_btPersona_clicked()
{
    dlgSeleccionarPersona *dlgPersona = new dlgSeleccionarPersona(this);
    dlgPersona->show();

    connect(dlgPersona, SIGNAL(personaEscogida(Persona)), this, SLOT(recibirPersona(Persona)));

}

void dlgDetalles::on_btLugar_clicked()
{
    dlgSeleccionarLugar *dlgLugar = new dlgSeleccionarLugar(this);
    dlgLugar->show();

    connect(dlgLugar, SIGNAL(lugarEscogido(Lugar)), this, SLOT(recibirLugar(Lugar)));

}

void dlgDetalles::cargarModelos(){

    /*
     * TODO: tal y como está esto estos completers no se van a actualizar
     * hasta que no se meta algo en la base de datos (bueno, ahora creo que ni con eso)
     * pero no pej cuando vaya metiendo cosas.
     * La posible solución sería pasar los datos del QSqlQueryModel
     * a un QStringList(model?) y añadir luego cosas nuevas a ese modelo
     */

    m_keys = new QSqlQueryModel(this);
    m_keys->setQuery("SELECT DISTINCT json_object_keys(detalle) FROM resoluciones_detalles ORDER BY json_object_keys(detalle);");

    keys_completer = new QCompleter(this);
    keys_completer->setModel(m_keys);
    keys_completer->setCompletionColumn(0);
    keys_completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->txtKey->setCompleter(keys_completer);

    m_values = new QSqlQueryModel(this);
    // ponemos una cosa general que luego habrá que precisar
    m_values->setQuery("SELECT DISTINCT value from resoluciones_detalles, json_each_text(detalle) ORDER BY value;");

    values_completer = new QCompleter(this);
    values_completer->setModel(m_values);
    values_completer->setCompletionColumn(0);
    values_completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->txtValue->setCompleter(values_completer);
}
