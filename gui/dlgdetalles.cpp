#include "dlgdetalles.h"
#include "ui_dlgdetalles.h"

#include "objs/jsongestor.h"
#include "dlgseleccionargeneral.h"
#include "dlgaprobacionesentrada.h"
#include "dlglicenciaentrada.h"
#include "dlgpenaentrada.h"
#include "dlgafiliacionentrada.h"
#include "dlgordenanzaentrada.h"

#include "models/qjsonmodel.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QJsonArray>

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

    json_model = new QJsonModel(this);
    ui->twJsonGeneral->setModel(json_model);

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

        ExtraInfos extras = aprobacion->getExtraInfos();
        anadirExtraInfos(extras);

        jsondetalles->nuevoBloqueJson();
    }
}

void dlgDetalles::recibirLicencia(Licencia licencia)
{
    /*
     * si el jsondetalles no está vacío, creamos un nuevo bloque
     */
    if (!jsondetalles->isEmpty())
        jsondetalles->nuevoBloqueJson();

    jsondetalles->anadirValor("licencia", "yes");
    if (!licencia.getLicenciatipo().isEmpty()) {
        jsondetalles->anadirValor("licencia_tipo", licencia.getLicenciatipo());
    }

    /*
     * TODO: aquí se plantea la duda qué hacer con los NULLs?
     * ¿controlo si están vacíos y no los meto? ¿o meto nulls que luego
     * a lo mejor es más interesante para buscar?
     */
    if (!licencia.getOtorgantes().isEmpty())
        jsondetalles->anadirValor("otorgante", QJsonArray::fromStringList(licencia.getOtorgantes()));

    if (!licencia.getReceptores().isEmpty())
        jsondetalles->anadirValor("receptor", QJsonArray::fromStringList(licencia.getReceptores()));

    if (!licencia.getAsunto().isEmpty())
        jsondetalles->anadirValor("asunto", licencia.getAsunto());

    jsondetalles->anadirValor("seguridad", QJsonValue(licencia.getSeguridad()));

    ExtraInfos extras = licencia.getExtraInfos();
    anadirExtraInfos(extras);

    QJsonObject lic_json = licencia.getLicenciaJson();
    json_model->anadirJson(lic_json);
}

void dlgDetalles::recibirPena(Pena pena)
{

    /*
     * si el jsondetalles no está vacío, creamos un nuevo bloque
     */
    if (!jsondetalles->isEmpty())
        jsondetalles->nuevoBloqueJson();

     jsondetalles->anadirValor("pena", "yes");

     /*
      * TODO: aquí se plantea la duda qué hacer con los NULLs?
      * ¿controlo si están vacíos y no los meto? ¿o meto nulls que luego
      * a lo mejor es más interesante para buscar?
      */
     if (!pena.getPenasTipos().isEmpty())
         jsondetalles->anadirValor("pena_tipos", QJsonArray::fromStringList(pena.getPenasTipos()));

     if (!pena.getDuracion().isEmpty())
         jsondetalles->anadirValor("duracion", QJsonValue(pena.getDuracion()));

     if (!pena.getPenados().isEmpty())
         jsondetalles->anadirValor("penados", QJsonArray::fromStringList(pena.getPenados()));

     if (!pena.getMotivo().isEmpty())
         jsondetalles->anadirValor("motivo", QJsonValue(pena.getMotivo()));

     if (!pena.getAbsolucion().isEmpty())
         jsondetalles->anadirValor("absolucion", QJsonValue(pena.getAbsolucion()));

     if (!pena.getPenaTexto().isEmpty())
         jsondetalles->anadirValor("pena_texto", QJsonValue(pena.getPenaTexto()));

     jsondetalles->anadirValor("seguridad", QJsonValue(pena.getSeguridad()));

     ExtraInfos extras = pena.getExtraInfos();
     anadirExtraInfos(extras);
}

void dlgDetalles::recibirAfiliacion(QList<Afiliacion *> lista_afiliaciones)
{
    if (lista_afiliaciones.size() == 0)
        return;

    /*
     * si el jsondetalles no está vacío, creamos un nuevo bloque
     */
    if (!jsondetalles->isEmpty())
        jsondetalles->nuevoBloqueJson();

    for (int i = 0; i < lista_afiliaciones.size(); ++i) {
        Afiliacion *afiliacion = lista_afiliaciones.at(i);

        jsondetalles->anadirValor("afiliación", "yes");
        jsondetalles->anadirValor("Persona", afiliacion->getPersona().getNombre(),
                                  afiliacion->getPersona().getId());

        // a veces probablemente no haya casa de origen...
        if (!afiliacion->getCasaOrigen().getNombre().isEmpty())
            jsondetalles->anadirValor("Casa_origen", afiliacion->getCasaOrigen().getNombre(),
                                      afiliacion->getCasaOrigen().getId());

        if (!afiliacion->getCasaDestino().getNombre().isEmpty())
            jsondetalles->anadirValor("Casa_destino", afiliacion->getCasaDestino().getNombre(),
                                      afiliacion->getCasaDestino().getId());

        if (!afiliacion->getProvinciaOrigen().getNombre().isEmpty())
            jsondetalles->anadirValor("Provincia_origen", afiliacion->getProvinciaOrigen().getNombre(),
                                      afiliacion->getProvinciaOrigen().getId());

        if (!afiliacion->getProvinciaDestino().getNombre().isEmpty())
            jsondetalles->anadirValor("Provincia_destino", afiliacion->getProvinciaDestino().getNombre(),
                                      afiliacion->getProvinciaDestino().getId());

        ExtraInfos extras = afiliacion->getExtras();
        anadirExtraInfos(extras);

        jsondetalles->nuevoBloqueJson();
    }

}

void dlgDetalles::recibirOrdenanza(Ordenanza ordenanza)
{

    /*
     * si el jsondetalles no está vacío, creamos un nuevo bloque
     */
    if (!jsondetalles->isEmpty())
        jsondetalles->nuevoBloqueJson();

    if (ordenanza.getTipo() == Ordenanza::TipoOrdenanza::PROHIBICION)
        jsondetalles->anadirValor("prohibición", "yes");
    else
        jsondetalles->anadirValor("mandato", "yes");

     /*
      * TODO: aquí se plantea la duda qué hacer con los NULLs?
      * ¿controlo si están vacíos y no los meto? ¿o meto nulls que luego
      * a lo mejor es más interesante para buscar?
      */
     if (!ordenanza.getObjetos().isEmpty())
         jsondetalles->anadirValor("objetos", QJsonArray::fromStringList(ordenanza.getObjetos()));

     if (!ordenanza.getReceptores().isEmpty())
         jsondetalles->anadirValor("destinatarios", QJsonArray::fromStringList(ordenanza.getReceptores()));

     if (!ordenanza.getRestriccion().isEmpty())
         jsondetalles->anadirValor("restricción", ordenanza.getRestriccion());

     jsondetalles->anadirValor("seguridad", QJsonValue(ordenanza.getSeguridad()));

     if (ordenanza.getPena().estaLleno()) {
        QJsonObject pena_json;
        pena_json.insert("penas_tipos", QJsonArray::fromStringList(ordenanza.getPena().getPenasTipos()));
        pena_json.insert("destinatarios_pena", QJsonArray::fromStringList(ordenanza.getPena().getPenados()));
        pena_json.insert("motivo", ordenanza.getPena().getMotivo());
        pena_json.insert("pena_texto", ordenanza.getPena().getPenaTexto());
        pena_json.insert("duración_pena", ordenanza.getPena().getDuracion());
        pena_json.insert("restricción_pena", ordenanza.getPena().getRestriccion());
        pena_json.insert("seguridad_pena", QJsonValue(ordenanza.getPena().getSeguridad()));

        ExtraInfos e = ordenanza.getPena().getExtraInfos();

        if (e.size() > 0 ) {
            for (int i = 0; i < e.size(); ++i) {
                QPair<QString, QString> valores;
                valores = e.at(i);

                pena_json.insert(valores.first, QJsonValue(valores.second));
            }
        }

        jsondetalles->anadirValor("pena", pena_json);
     }

     if (ordenanza.getRetroReferencia().estaLleno()) {
         QJsonObject retro_json = ordenanza.getRetroReferencia().getRetroJson();
         jsondetalles->anadirValor("retro", retro_json);
     }

     if (!ordenanza.getTemas().isEmpty()) {
         QList<int> temas = ordenanza.getTemas();
         QJsonArray array_temas;

         for (int i = 0; i < temas.size(); ++i) {
             array_temas.append(QJsonValue(temas.at(i)));
         }

         jsondetalles->anadirValor("temas", array_temas);
     }

     ExtraInfos extras = ordenanza.getExtraInfos();
     anadirExtraInfos(extras);
}

void dlgDetalles::recibirCasa(Casa casa){
    jsondetalles->anadirValor("Casa", casa.getNombre(), casa.getId());
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

    connect(dlgSeleccionar, SIGNAL(casaEscogidaSignal(Casa)), this, SLOT(recibirCasa(Casa)));

}

void dlgDetalles::on_btAfiliaciones_clicked()
{
    dlgAfiliacionEntrada *dlgafiliaciones = new dlgAfiliacionEntrada(this);
    dlgafiliaciones->show();

    connect(dlgafiliaciones, SIGNAL(aceptarDatos(QList<Afiliacion*>)), this, SLOT(recibirAfiliacion(QList<Afiliacion*>)));

}

void dlgDetalles::on_btOrdenanzas_clicked()
{
    dlgOrdenanzaEntrada *dlgordenanzas = new dlgOrdenanzaEntrada(this);
    dlgordenanzas->show();

    connect(dlgordenanzas, SIGNAL(aceptarOrdenanza(Ordenanza)), this, SLOT(recibirOrdenanza(Ordenanza)));

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

void dlgDetalles::anadirExtraInfos(ExtraInfos extras)
{
    /*
     * este método sirve para que lo usen los diversos
     * formularios que me permiten meter penas, licencias, etc.
     */

    if (extras.size() > 0 ) {
        for (int i = 0; i < extras.size(); ++i) {
            QPair<QString, QString> valores;
            valores = extras.at(i);

            jsondetalles->anadirValor(valores.first, QJsonValue(valores.second));
        }
    }
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

    connect(dlglicencias, SIGNAL(aceptarLicencia(Licencia)), this, SLOT(recibirLicencia(Licencia)));

}

void dlgDetalles::on_btPenas_clicked() {

    dlgPenaEntrada *dlgpena = new dlgPenaEntrada(this);
    dlgpena->show();

    connect(dlgpena, SIGNAL(aceptarPena(Pena)), this, SLOT(recibirPena(Pena)));

}
