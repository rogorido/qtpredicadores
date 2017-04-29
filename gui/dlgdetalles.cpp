#include "dlgdetalles.h"
#include "ui_dlgdetalles.h"

#include "objs/jsongestor.h"
#include "dlgseleccionargeneral.h"
#include "dlgaprobacionesentrada.h"
#include "dlglicenciaentrada.h"

#include <QSqlQueryModel>
#include <QCompleter>

#include <QDebug>

const QString sqlresoluciones_valores="SELECT DISTINCT value from resolutions_details, jsonb_each_text(details) ORDER BY value;";
const QString sqlresoluciones_keys="SELECT DISTINCT jsonb_object_keys(details) FROM resolutions_details ORDER BY jsonb_object_keys(details);";
const QString sqlobras_valores="SELECT DISTINCT value from works_details, jsonb_each_text(details) ORDER BY value;";
const QString sqlobras_keys="SELECT DISTINCT jsonb_object_keys(details) FROM works_details ORDER BY jsonb_object_keys(details);";
const QString sqlpersonas_valores="SELECT DISTINCT value from persons_details, jsonb_each_text(details) ORDER BY value;";
const QString sqlpersonas_keys="SELECT DISTINCT jsonb_object_keys(details) FROM persons_details ORDER BY jsonb_object_keys(details);";


dlgDetalles::dlgDetalles(JsonGestor *json, int t, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgDetalles), jsondetalles(json), tipo(t)
{
    ui->setupUi(this);
    jsondetalles->setTreeWidget(ui->twDetalles);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(hide()));
    connect(ui->btNuevoBloque, SIGNAL(clicked(bool)), jsondetalles, SLOT(nuevoBloqueJson()));
    connect(ui->btBorrarElemento, SIGNAL(clicked(bool)), jsondetalles, SLOT(eliminarElemento()));

    // esto hay en todo caso que mejorarlo pq ahora tenemos diversas queries según el origen
    // pero tvz no haga falta y se pueda quitar sin más
    //connect(ui->txtKey, SIGNAL(editingFinished()), this, SLOT(actualizarCompleterValues()));

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

void dlgDetalles::recibirProvincia(Provincia provincia){
    int id = provincia.getId();
    QString valor = provincia.getNombre();

    jsondetalles->anadirValor("Provincia", valor, id);
}

void dlgDetalles::recibirAprobaciones(QList<Aprobacion *> lista_aprobaciones)
{

    /*
     * tenemos que meter los datos de esta lista de aprobaciones
     * en nuestro json. Pero: ¿todo esto no es un poco lío? ¿No habría
     * una forma un poco más fácil de hacerlo?
     */

    if (lista_aprobaciones.size() == 0)
        return;

    /*
     * si el jsondetalles no está vacío, creamos un nuevo bloque
     */
    if (!jsondetalles->isEmpty())
        jsondetalles->nuevoBloqueJson();

    for (int i = 0; i < lista_aprobaciones.size(); ++i) {
        Aprobacion *aprobacion = lista_aprobaciones.at(i);

        QString nombre = aprobacion->getPersona().getNombre() + ' ' + aprobacion->getPersona().getApellidos();
        jsondetalles->anadirValor("aprobación", aprobacion->getTipo());
        jsondetalles->anadirValor("Persona", nombre, aprobacion->getPersona().getId());

        // a veces probablemente no haya provincia...
        QString provincia = aprobacion->getProvincia().getNombre();
        if (!provincia.isEmpty())
            jsondetalles->anadirValor("Provincia", aprobacion->getProvincia().getNombre(), aprobacion->getProvincia().getId());

        jsondetalles->nuevoBloqueJson();
    }
}

void dlgDetalles::recibirCasa(int id, QString valor){
    jsondetalles->anadirValor("Casa", valor, id);
}

void dlgDetalles::actualizarCompleterValues(){
    QString key;

    key = ui->txtKey->text();

    if (!key.isEmpty())
        m_values->setQuery(QString("SELECT DISTINCT value from resolutions_details, json_each_text(details) "
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

void dlgDetalles::on_btProvincia_clicked()
{
    dlgSeleccionarGeneral *dlgSeleccionar = new dlgSeleccionarGeneral(PROVINCIA, this);
    dlgSeleccionar->show();

    connect(dlgSeleccionar, SIGNAL(provinciaEscogidaSignal(Provincia)), this, SLOT(recibirProvincia(Provincia)));

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
    switch (tipo) {
    case RESOLUCION:
        m_keys->setQuery(sqlresoluciones_keys);
        break;
    case PERSONADETALLES:
        m_keys->setQuery(sqlpersonas_keys);
        break;
    case OBRA:
        m_keys->setQuery(sqlobras_keys);
        break;
    default:
        /*
         * en caso de 0 ponemos el de resoluciones, aunque en principio
         * para que no dé error...
         */
        m_keys->setQuery(sqlresoluciones_keys);
        break;
    }

    keys_completer = new QCompleter(this);
    keys_completer->setModel(m_keys);
    keys_completer->setCompletionColumn(0);
    keys_completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->txtKey->setCompleter(keys_completer);

    m_values = new QSqlQueryModel(this);
    switch (tipo) {
    case RESOLUCION:
        qDebug() << "estamos aquí";
        m_values->setQuery(sqlresoluciones_valores);
        break;
    case PERSONADETALLES:
        m_values->setQuery(sqlpersonas_valores);
        break;
    case OBRA:
        m_values->setQuery(sqlobras_valores);
        break;
    default:
        /*
         * en caso de 0 ponemos el de resoluciones, aunque en principio
         * para que no dé error...
         */
        m_values->setQuery(sqlresoluciones_valores);
        break;
    }

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

void dlgDetalles::on_btAprobaciones_clicked(){

    dlgAprobacionesEntrada *dlgaprobaciones = new dlgAprobacionesEntrada(this);
    dlgaprobaciones->show();

    connect(dlgaprobaciones, SIGNAL(aceptarDatos(QList<Aprobacion*>)), this, SLOT(recibirAprobaciones(QList<Aprobacion*>)));
}

void dlgDetalles::on_btLicencias_clicked() {

    dlgLicenciaEntrada *dlglicencias = new dlgLicenciaEntrada(this);
    dlglicencias->show();


}
