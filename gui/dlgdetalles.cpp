#include "dlgdetalles.h"
#include "ui_dlgdetalles.h"

#include "objs/jsongestor.h"
#include "dlgseleccionargeneral.h"

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
    connect(ui->btBorrarElemento, SIGNAL(clicked(bool)), jsondetalles, SLOT(eliminarElemento()));
    connect(ui->txtKey, SIGNAL(editingFinished()), this, SLOT(actualizarCompleterValues()));

    ui->cboDescripcion->addItem("Nombramiento");
    ui->cboDescripcion->setCurrentIndex(-1);

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

void dlgDetalles::recibirCasa(int id, QString valor){
    jsondetalles->anadirValor("Casa", valor, id);
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
    dlgSeleccionarGeneral *dlgSeleccionar = new dlgSeleccionarGeneral(PERSONA, this);
    dlgSeleccionar->show();

    connect(dlgSeleccionar, SIGNAL(personaEscogidaSignal(Persona)), this, SLOT(recibirPersona(Persona)));

}

void dlgDetalles::on_btLugar_clicked()
{
    dlgSeleccionarGeneral *dlgSeleccionar = new dlgSeleccionarGeneral(LUGAR, this);
    dlgSeleccionar->show();

    connect(dlgSeleccionar, SIGNAL(lugarEscogidoSignal(Lugar)), this, SLOT(recibirLugar(Lugar)));

}

void dlgDetalles::on_btCasa_clicked()
{
    dlgSeleccionarGeneral *dlgSeleccionar = new dlgSeleccionarGeneral(CASA, this);
    dlgSeleccionar->show();

    connect(dlgSeleccionar, SIGNAL(casaEscogidaSignal(int,QString)), this, SLOT(recibirCasa(int,QString)));

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

void dlgDetalles::on_btJsonAnadirLibre_clicked()
{
    QString key = ui->txtKey->text();
    QString value = ui->txtValue->text();

    if (!key.isEmpty() && !value.isEmpty()){
        jsondetalles->anadirValor(key, value);

        ui->txtKey->setText("");
        ui->txtValue->setText("");
    }
}

void dlgDetalles::on_btJsonAnadirDescripcion_clicked(){

    QString valor = ui->cboDescripcion->currentText();

    if (!valor.isEmpty())
        jsondetalles->anadirValor("Tipo", QJsonValue(valor));

}

void dlgDetalles::on_btModificarDetalles_toggled(bool checked)
{
    if (checked){
        ui->btModificarDetalles->setText("Modificando");
    }
    else
        ui->btModificarDetalles->setText("Añadiendo");
}

void dlgDetalles::on_btAnadirInteresante_clicked(){

    int interesante = ui->spInteresante->value();

    jsondetalles->anadirValor("Interesante", QJsonValue(interesante));
}

