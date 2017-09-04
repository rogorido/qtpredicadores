#include "dlgdetalles.h"
#include "ui_dlgdetalles.h"

#include "dlgseleccionargeneral.h"
#include "dlgaprobacionesentrada.h"
#include "dlglicenciaentrada.h"
#include "dlgpenaentrada.h"
#include "dlgafiliacionentrada.h"
#include "dlgordenanzaentrada.h"
#include "dlgsufragiosentrada.h"
#include "dlgdeclaracionentrada.h"

#include "models/qjsonmodel.h"

#include "widgets/myqmdiarea.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QJsonArray>
#include <QTreeWidgetItem>
#include <QJsonObject>
#include <QMdiSubWindow>

#include <QDebug>

const QString sqlresoluciones_valores="SELECT DISTINCT value from resolutions_details, jsonb_each_text(details) ORDER BY value;";
const QString sqlresoluciones_keys="SELECT DISTINCT jsonb_object_keys(details) FROM resolutions_details ORDER BY jsonb_object_keys(details);";
const QString sqlobras_valores="SELECT DISTINCT value from works_details, jsonb_each_text(details) ORDER BY value;";
const QString sqlobras_keys="SELECT DISTINCT jsonb_object_keys(details) FROM works_details ORDER BY jsonb_object_keys(details);";
const QString sqlpersonas_valores="SELECT DISTINCT value from persons_details, jsonb_each_text(details) ORDER BY value;";
const QString sqlpersonas_keys="SELECT DISTINCT jsonb_object_keys(details) FROM persons_details ORDER BY jsonb_object_keys(details);";


dlgDetalles::dlgDetalles(QJsonModel *json, int t, bool anadir, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgDetalles), json_model(json), tipo(t), anadiendo(anadir)
{
    ui->setupUi(this);

    mdiarea = MyQmdiArea::Instance(this);

    ui->twJsonGeneral->setModel(json_model);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));

    /*
     * si estamos añadiendo cerramos sin más; si no, lo ocultamos.
     * Al cerrar tenemos que emitir de todas formas una señal.
     */
    if (anadir) {
        connect(ui->btOK, SIGNAL(clicked(bool)), this, SIGNAL(accepted()));
        connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    }
    else
        connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(ocultar()));

    ui->twJsonLibre->setColumnCount(2);

    ui->txtKey->installEventFilter(this);
    ui->txtValue->installEventFilter(this);
    ui->spInteresante->installEventFilter(this);

    cargarModelos();
}

dlgDetalles::~dlgDetalles()
{
    delete ui;
}

void dlgDetalles::recibirPersona(Persona persona){
    int id = persona.getId();
    QString valor = persona.getNombre() + ' ' + persona.getApellidos();

    json_libre.insert("persona", id);
    anadirChildItem("persona", valor);
}

void dlgDetalles::recibirLugar(Lugar lugar){
    int id = lugar.getId();
    QString valor = lugar.getLugar();

    json_libre.insert("lugar", id);
    anadirChildItem("lugar", valor);
}

void dlgDetalles::recibirProvincia(Provincia provincia){
    int id = provincia.getId();
    QString valor = provincia.getNombre();

    json_libre.insert("provincia", id);
    anadirChildItem("provincia", valor);
}

void dlgDetalles::recibirAprobaciones(QList<Aprobacion *> lista_aprobaciones)
{
    for (int i = 0; i < lista_aprobaciones.size(); ++i) {
        Aprobacion *aprobacion = lista_aprobaciones.at(i);

        QJsonObject aprobacion_json = aprobacion->getAprobacionJson();
        json_model->anadirJson(aprobacion_json);
    }

    json_model->resetearModelo();
}

void dlgDetalles::recibirLicencia(Licencia licencia)
{
    QJsonObject lic_json = licencia.getLicenciaJson();
    json_model->anadirJson(lic_json);
    json_model->resetearModelo();
}

void dlgDetalles::recibirPena(Pena pena)
{
     QJsonObject pena_json = pena.getPenaJson();
     json_model->anadirJson(pena_json);
     json_model->resetearModelo();
}

void dlgDetalles::recibirAfiliacion(QList<Afiliacion *> lista_afiliaciones)
{
    for (int i = 0; i < lista_afiliaciones.size(); ++i) {
        Afiliacion *afiliacion = lista_afiliaciones.at(i);

        QJsonObject afiliacion_json = afiliacion->getAfiliacionJson();
        json_model->anadirJson(afiliacion_json);
    }
    json_model->resetearModelo();

}

void dlgDetalles::recibirOrdenanza(Ordenanza ordenanza)
{
     QJsonObject ordenanza_json = ordenanza.getOrdenanzaJson();
     json_model->anadirJson(ordenanza_json);
     json_model->resetearModelo();
}

void dlgDetalles::recibirSufragio(Sufragio sufragio)
{
    QJsonObject sufragio_json = sufragio.getSufragioJson();
    json_model->anadirJson(sufragio_json);
    json_model->resetearModelo();
}

void dlgDetalles::recibirTraslado(Diocesis diocesis)
{
    QJsonObject json;

    json.insert("traslado", QJsonValue(diocesis.getId()));
    json_model->anadirJson(json);
    json_model->resetearModelo();
}

void dlgDetalles::recibirDeclaracion(Declaracion declaracion)
{
    QJsonObject declaracion_json = declaracion.getDeclaracionJson();
    json_model->anadirJson(declaracion_json);
    json_model->resetearModelo();
}

void dlgDetalles::recibirCasa(Casa casa){

    json_libre.insert("casa", casa.getId());
    anadirChildItem("casa", casa.getNombre());

}

void dlgDetalles::actualizarCompleterValues(){
    QString key;

    key = ui->txtKey->text();

    if (!key.isEmpty())
        m_values->setQuery(QString("SELECT DISTINCT value from resolutions_details, json_each_text(details) "
                               "WHERE key='%1' ORDER BY value;").arg(key));

}

void dlgDetalles::anadirChildItem(const QString &key, const QString &value)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->twJsonLibre);
    item->setText(0, key);
    item->setText(1, value);

}

void dlgDetalles::cerrar()
{
    parentWidget()->close();
}

void dlgDetalles::ocultar()
{
    parentWidget()->hide();
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
    connect(dlgafiliaciones, SIGNAL(aceptarDatos(QList<Afiliacion*>)), this, SLOT(recibirAfiliacion(QList<Afiliacion*>)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgafiliaciones);
    window->show();
}

void dlgDetalles::on_btOrdenanzas_clicked()
{
    dlgOrdenanzaEntrada *dlgordenanzas = new dlgOrdenanzaEntrada(this);
    connect(dlgordenanzas, SIGNAL(aceptarOrdenanza(Ordenanza)), this, SLOT(recibirOrdenanza(Ordenanza)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgordenanzas);
    window->show();
}

void dlgDetalles::on_btDeclaraciones_clicked()
{
    dlgDeclaracionEntrada *dlgdeclaraciones = new dlgDeclaracionEntrada(this);
    connect(dlgdeclaraciones, SIGNAL(aceptarDeclaracion(Declaracion)), this, SLOT(recibirDeclaracion(Declaracion)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgdeclaraciones);
    window->show();
}

void dlgDetalles::on_btBorrarJsonLibre_clicked()
{
    ui->twJsonLibre->clear();

    /*
     * borramos el jodido json_libre, que al NO ser un pointer
     * no sé cómo inicializarlo, porque QJsonObject no sé por qué
     * no tiene un método clear()...
     * Uso este iterator que tp me queda muy claro, pero bueno...
     */
    QJsonObject::iterator i = json_libre.begin();
    while (i != json_libre.end()) {
        i = json_libre.erase(i);
    }

}

void dlgDetalles::on_btAnadirJsonLibre_clicked()
{
    json_model->anadirJson(json_libre);
    on_btBorrarJsonLibre_clicked();

    ui->tabWidget->setCurrentIndex(0);
}

void dlgDetalles::on_btBorrarBloqueJson_clicked()
{
    /*
     * la idea es la siguiente: cogemos el índice; si no es válido
     * salimos sin más. Si es válido continúa y coge el del padre.
     * Y aquí está el truco: si el índice del padre no es válido, eso
     * quiere decir que estamos ya en el nivel superior y por tanto
     * el índice que nos interesa es idx, pero si es válido, lo que
     * nos interesa es el índice padre.
     *
     * NOTE: esto evidentemente sólo sirve cuando hay solo un subnivel,
     * si hubiera más subniveles no funcionaría!
     */
    QModelIndex idx = ui->twJsonGeneral->currentIndex();
    int ordinal;

    if (!idx.isValid())
        return;

    QModelIndex padre = idx.parent();

    if (!padre.isValid())
        ordinal = idx.row();
    else
        ordinal = padre.row();

    json_model->borrarJson(ordinal);

}

void dlgDetalles::on_btSufragios_clicked()
{
    dlgSufragiosEntrada *dlgsufragio = new dlgSufragiosEntrada(this);
    connect(dlgsufragio, SIGNAL(emitirSufragio(Sufragio)), this, SLOT(recibirSufragio(Sufragio)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgsufragio);
    window->show();
}

void dlgDetalles::on_btTraslado_clicked()
{
    dlgSeleccionarGeneral *seleccionar = new dlgSeleccionarGeneral(DIOCESIS, this);
    connect(seleccionar, SIGNAL(diocesisEscogidaSignal(Diocesis)), this, SLOT(recibirTraslado(Diocesis)));

    QMdiSubWindow *window = mdiarea->addSubWindow(seleccionar);
    window->show();
}

void dlgDetalles::on_btAdmoniciones_clicked()
{
    dlgOrdenanzaEntrada *dlgordenanzas = new dlgOrdenanzaEntrada(this);
    connect(dlgordenanzas, SIGNAL(aceptarOrdenanza(Ordenanza)), this, SLOT(recibirOrdenanza(Ordenanza)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgordenanzas);
    window->show();
}


void dlgDetalles::on_btComisiones_clicked()
{
    dlgOrdenanzaEntrada *dlgordenanzas = new dlgOrdenanzaEntrada(this);
    connect(dlgordenanzas, SIGNAL(aceptarOrdenanza(Ordenanza)), this, SLOT(recibirOrdenanza(Ordenanza)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgordenanzas);
    window->show();
}

void dlgDetalles::anadirDatosLibres()
{
    QString key = ui->txtKey->text();
    QString value = ui->txtValue->text();

    if (!key.isEmpty() && !value.isEmpty()){
        json_libre.insert(key, value);

        ui->txtKey->setText("");
        ui->txtValue->setText("");
        ui->txtKey->setFocus();

        anadirChildItem(key, value);
    }
}

void dlgDetalles::anadirInteresante()
{
    int interesante = ui->spInteresante->value();
    json_libre.insert("Interesante", QJsonValue(interesante));
    anadirChildItem("interesante", QString::number(interesante));
}

bool dlgDetalles::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type()== QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
            if (keyEvent->key() == Qt::Key_Return){

                // y ahora dependiendo del QLineEdit...
                if (obj == ui->txtKey){
                    ui->txtValue->setFocus();
                    return true;
                }
                else if (obj == ui->txtValue) {
                    anadirDatosLibres();
                    return true;
                }
                else if (obj == ui->spInteresante) {
                    anadirInteresante();
                    return true;
                }
            }
        }

    /*
     * atención aquí lo importante es poner QWidget!
     * si pongo dlgPenaEntrada no funciona!!
     */
    return QWidget::eventFilter(obj, e);

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

void dlgDetalles::on_btAprobaciones_clicked(){

    dlgAprobacionesEntrada *dlgaprobaciones = new dlgAprobacionesEntrada(this);
    connect(dlgaprobaciones, SIGNAL(aceptarDatos(QList<Aprobacion*>)), this, SLOT(recibirAprobaciones(QList<Aprobacion*>)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgaprobaciones);
    window->show();
}

void dlgDetalles::on_btLicencias_clicked() {

    dlgLicenciaEntrada *dlglicencias = new dlgLicenciaEntrada(this);
    connect(dlglicencias, SIGNAL(aceptarLicencia(Licencia)), this, SLOT(recibirLicencia(Licencia)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlglicencias);
    window->show();
}

void dlgDetalles::on_btPenas_clicked() {

    dlgPenaEntrada *dlgpena = new dlgPenaEntrada(this);
    connect(dlgpena, SIGNAL(aceptarPena(Pena)), this, SLOT(recibirPena(Pena)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgpena);
    window->show();

}
