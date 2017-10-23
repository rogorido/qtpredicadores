#include "dlgnuevoobispo.h"
#include "ui_dlgnuevoobispo.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QJsonDocument>
#include <QCompleter>
#include <QMessageBox>
#include <QMdiSubWindow>
#include <QDebug>

#include "objs/obispo.h"
#include "objs/notas.h"
#include "models/qjsonmodel.h"
#include "dlgseleccionargeneral.h"
#include "dlgfuenteentrada.h"

#include "widgets/myqmdiarea.h"

const QDate fechainicial = QDate(1200, 1, 1);
const QDate fechafinal = QDate(1800, 1, 1);

dlgNuevoObispo::dlgNuevoObispo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgNuevoObispo)
{
    ui->setupUi(this);

    mdiarea = MyQmdiArea::Instance(this);

    ui->dtFechaInicio->setMinimumDate(fechainicial);
    ui->dtFechaInicio->setMaximumDate(fechafinal);
    ui->dtFechaFinal->setMinimumDate(fechainicial);
    ui->dtFechaFinal->setMaximumDate(fechafinal);
    ui->dtFechaInicio->setDate(fechainicial);
    ui->dtFechaFinal->setDate(fechainicial);

    // hay que inicializar el pointer para que no dé error luego.
    fuentedatos = new QJsonObject();

    json_detalles = new QJsonModel(this);

    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(cerrar()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarObispo()));
    connect(ui->btFuente, SIGNAL(clicked()), this, SLOT(anadirFuente()));
    connect(ui->txtPersona, SIGNAL(dobleclick()), this, SLOT(anadirPersona()));
    connect(ui->txtDiocesis, SIGNAL(dobleclick()), this, SLOT(anadirDiocesis()));
    connect(ui->btDetalles, SIGNAL(clicked()), this, SLOT(anadirDetalles()));
    connect(ui->dtFechaInicio, SIGNAL(dateChanged(QDate)), this, SLOT(fechaInicioCambiada()));
    connect(ui->dtFechaFinal, SIGNAL(dateChanged(QDate)), this, SLOT(fechaFinalCambiada()));

    cargarModelos();
}

dlgNuevoObispo::~dlgNuevoObispo()
{
    delete ui;
}

void dlgNuevoObispo::aceptarObispo()
{
    QSqlQuery query;
    QModelIndex idx;

    QString papa_seleccionado = ui->txtPapa->text();

    if (!papa_seleccionado.isEmpty())
        papa_id = extraerPapa(papa_seleccionado);

    if (persona_id == 0 || diocesis_id == 0){
        int ret = QMessageBox::warning(this, "Faltan datos",
                                       "Faltan datos: los campos persona, diócesis y papa son obligatorios.");
        Q_UNUSED(ret)
        return;
    }

    QString duracion = ui->txtDuracion->text();
    bool circa_fecha = ui->ckFechaAprox->isChecked();
    bool volver_mirar = ui->ckVolverMirar->isChecked();
    bool fin_muerte = ui->ckFinPorMuerte->isChecked();
    bool en_gcatholic = ui->ckGcatholic->isChecked();
    bool sufraganeo = ui->ckSufraganeo->isChecked();
    QDate fecha_inicio = ui->dtFechaInicio->date();
    QDate fecha_fin = ui->dtFechaFinal->date();

    /*
     * ATENCIÓn: aquí lo que hago es dereferenciar un pointer,
     * porque QJsonDocument me pide una referencia y fuentedatos
     * es un pointer...
     */
    QJsonDocument jsondoc(*fuentedatos);
    QString fuente_final = jsondoc.toJson(QJsonDocument::Compact);

    /*
     * TODO: faltaría lo de other_data, que es difernete de lo que
     * está en la tabla bishops_details...
     */
    query.prepare("INSERT INTO bishops.bishops(bishop_person_id, diocese_id, pope_id, "
                  "date_nomination, circa_date_nomination, date_end, duration, end_bydeath, "
                  "in_gcatholic, suffragean, see_again, other_data) "
                  "VALUES(:persona, :diocesis, :papa, "
                  ":fecha_inicio, :circa_fecha, :fecha_final, :duracion, :finpormuerte, "
                  ":gcatholic, :sufraganeo, :volveramirar, :otrosdatos)");
    query.bindValue(":persona", persona_id);
    query.bindValue(":diocesis", diocesis_id);

    if (papa_id != 0)
        query.bindValue(":papa", papa_id);
    else
        query.bindValue(":papa", QVariant(QVariant::Int));

    if (fecha_inicio_cambiada)
        query.bindValue(":fecha_inicio", fecha_inicio);
    else
        query.bindValue(":fecha_inicio", QVariant(QVariant::Date));

    if (fecha_final_cambiada)
        query.bindValue(":fecha_final", fecha_fin);
    else{
        qDebug() << "no se ha cambadio la fecha...";
        query.bindValue(":fecha_final", QVariant(QVariant::Date));
    }

    query.bindValue(":circa_fecha", circa_fecha);
    query.bindValue(":duracion", duracion);
    query.bindValue(":finpormuerte", fin_muerte);
    query.bindValue(":gcatholic", en_gcatholic);
    query.bindValue(":sufraganeo", sufraganeo);
    query.bindValue(":volveramirar", volver_mirar);

    if (fuente_recibida)
        query.bindValue(":otrosdatos", fuente_final);
    else
        query.bindValue(":otrosdatos", QVariant(QVariant::String));

    if (query.exec()){
        QSqlQuery lastid("select max(bishop_id) from bishops.bishops");

        lastid.first();
        int id = lastid.value(0).toInt();

        introducirJson(id);
        introducirNotas(id);
        borrarCampos();
    }
    else {
        int ret = QMessageBox::warning(this, "Error",
                                       "Ha habido un error al ejecutar la consulta de inserción.");
        Q_UNUSED(ret)
        qDebug() << query.lastError();
        return;
    }

}

void dlgNuevoObispo::anadirPersona()
{
    dlgSeleccionarGeneral *seleccionar = new dlgSeleccionarGeneral(PERSONA, this);
    connect(seleccionar, SIGNAL(personaEscogidaSignal(Persona)), this, SLOT(recibirPersona(Persona)));

    QMdiSubWindow *window = mdiarea->addSubWindow(seleccionar);
    window->show();
}

void dlgNuevoObispo::anadirDiocesis()
{
    dlgSeleccionarGeneral *seleccionar = new dlgSeleccionarGeneral(DIOCESIS, this);
    connect(seleccionar, SIGNAL(diocesisEscogidaSignal(Diocesis)), this, SLOT(recibirDiocesis(Diocesis)));

    QMdiSubWindow *window = mdiarea->addSubWindow(seleccionar);
    window->show();
}

void dlgNuevoObispo::anadirFuente()
{
    dlgFuenteEntrada *dlgfuente = new dlgFuenteEntrada(this);
    connect(dlgfuente, SIGNAL(signalFuente(fuente)), this, SLOT(recibirFuente(fuente)));

    dlgfuente->show();
}

void dlgNuevoObispo::anadirDetalles()
{
    dlgdetalles = new dlgDetalles(json_detalles, OBISPO, false, this);

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgdetalles);
    window->show();
}

void dlgNuevoObispo::fechaInicioCambiada()
{
    fecha_inicio_cambiada = true;
}

void dlgNuevoObispo::fechaFinalCambiada()
{
    fecha_final_cambiada = true;
}

void dlgNuevoObispo::recibirPersona(Persona persona)
{
    persona_id = persona.getId();

    QString persona_mostrar;
    persona_mostrar = persona.getNombre() + QString(' ') + persona.getApellidos() + QString(' ') + persona.getOrigen();

    ui->txtPersona->setText(persona_mostrar);

}

void dlgNuevoObispo::recibirDiocesis(Diocesis diocesis)
{
    diocesis_id = diocesis.getId();

    ui->txtDiocesis->setText(diocesis.getNombre());
}

void dlgNuevoObispo::recibirFuente(fuente datoobra)
{
    QJsonObject json_datosconcretos;

    fuente_recibida = true;

    json_datosconcretos.insert("source_id", QJsonValue(datoobra.titulo));
    json_datosconcretos.insert("volume", datoobra.tomo);
    json_datosconcretos.insert("pages", datoobra.paginas);

    fuentedatos->insert("source", json_datosconcretos);
}

void dlgNuevoObispo::cerrar()
{
    parentWidget()->close();
}

void dlgNuevoObispo::introducirJson(const int id)
{
    QSqlQuery query;
    int totaljson;

    totaljson = json_detalles->getSize();

    if (totaljson == 0)
        return;

    for (int var = 0; var < totaljson; ++var) {

        QString jsonfinal = json_detalles->getJsonString(var);

        query.prepare("INSERT INTO bishops_details(bishop_id, details) VALUES(:bishopid, :json)");
        query.bindValue(":bishopid", id);
        query.bindValue(":json", jsonfinal);
        if (!query.exec()){
            int ret = QMessageBox::warning(this, "Error",
                                           "Ha habido un error al ejecutar la consulta de inserción.");
            Q_UNUSED(ret)
            qDebug() << query.lastError();
        }
    }
}

void dlgNuevoObispo::introducirNotas(const int id)
{
    /*
     * esto tiene que ser más fácil. Demasiado liado!
     */
    QSqlQuery query;
    Notas notas;
    QJsonObject notas_json;
    QJsonObject notas_final;
    QString jsonfinal;

    if (!ui->wdNotas->haCambiado())
        return;

    notas = ui->wdNotas->getNotas();
    notas_json = notas.getNotasJson();
    notas_final.insert("meta_info", notas_json);

    QJsonDocument notas_doc(notas_final);
    jsonfinal = notas_doc.toJson(QJsonDocument::Compact);
    query.prepare("INSERT INTO bishops_details(bishop_id, details) VALUES(:bishopid, :json)");
    query.bindValue(":bishopid", id);
    query.bindValue(":json", jsonfinal);

    if (!query.exec()){
        int ret = QMessageBox::warning(this, "Error",
                                       "Ha habido un error al ejecutar la consulta de inserción.");
        Q_UNUSED(ret)
        qDebug() << query.lastError();
        return;
    }
}

void dlgNuevoObispo::cargarModelos()
{
    m_papas = new QSqlQueryModel(this);
    m_papas->setQuery("SELECT pope_id, name_pope FROM general.popes ORDER BY name_pope");

    m_papas_completer = new QCompleter(this);
    m_papas_completer->setModel(m_papas);
    m_papas_completer->setCompletionColumn(1);
    m_papas_completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->txtPapa->setCompleter(m_papas_completer);
}

void dlgNuevoObispo::borrarCampos()
{
    persona_id = 0;
    diocesis_id = 0;
    papa_id = 0;

    ui->txtPersona->setText("");
    ui->txtDiocesis->setText("");
    ui->txtPapa->setText("");
    ui->txtDuracion->setText("");

    fecha_inicio_cambiada = false;
    fecha_final_cambiada = false;

    ui->ckFechaAprox->setCheckState(Qt::Unchecked);
    ui->ckFinPorMuerte->setCheckState(Qt::Unchecked);
    ui->ckVolverMirar->setCheckState(Qt::Unchecked);
    ui->ckGcatholic->setCheckState(Qt::Unchecked);
    ui->ckSufraganeo->setCheckState(Qt::Unchecked);

    ui->dtFechaInicio->setDate(fechainicial);
    ui->dtFechaFinal->setDate(fechainicial);

    ui->wdNotas->reiniciar();

     json_detalles = new QJsonModel(this);

    /*
     * no borramos el punto fuentedatos
     * pque ahora no sé cómo borrar un pointer
     * pero en principio conesta variable debería ser
     * suficiente
     */
    //fuentedatos = QJsonObject();
    fuente_recibida = false;

    ui->txtPersona->setFocus();
}

int dlgNuevoObispo::extraerPapa(QString papa)
{

    QSqlQuery query;
    int papa_extraido;

    query.prepare("SELECT pope_id FROM popes where name_pope = :nombre");
    query.bindValue(":nombre", papa);
    query.exec();
    query.first();

    if (query.size() == 0)
        return 0;

    papa_extraido = query.value(0).toInt();
    return papa_extraido;

}
