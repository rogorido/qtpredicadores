#include "dlgnuevoobispo.h"
#include "ui_dlgnuevoobispo.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QJsonDocument>
#include <QCompleter>
#include <QMessageBox>
#include <QDebug>

#include "objs/obispo.h"
#include "models/qjsonmodel.h"
#include "dlgseleccionargeneral.h"
#include "dlgfuenteentrada.h"

dlgNuevoObispo::dlgNuevoObispo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevoObispo)
{
    ui->setupUi(this);

    QDate fechainicial = QDate(1200, 1, 1);
    QDate fechafinal = QDate(1800, 1, 1);

    ui->dtFechaInicio->setMinimumDate(fechainicial);
    ui->dtFechaInicio->setMaximumDate(fechafinal);
    ui->dtFechaFinal->setMinimumDate(fechainicial);
    ui->dtFechaFinal->setMaximumDate(fechafinal);
    ui->dtFechaInicio->setDate(fechainicial);

    // hay que inicializar el pointer para que no dé error luego.
    fuentedatos = new QJsonObject();

    json_detalles = new QJsonModel(this);
    /*
     * FIXME: aquí el 2º paramétro lo dejo como OBRA pq
     * sinceramente no sabría qué poner ahora...
     */
    dlgdetalles = new dlgDetalles(json_detalles, OBRA, false, this);

    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarObispo()));
    connect(ui->btFuente, SIGNAL(clicked()), this, SLOT(anadirFuente()));
    connect(ui->txtPersona, SIGNAL(dobleclick()), this, SLOT(anadirPersona()));
    connect(ui->txtDiocesis, SIGNAL(dobleclick()), this, SLOT(anadirDiocesis()));
    connect(ui->dtFechaInicio, SIGNAL(dateChanged(QDate)), this, SLOT(fechaInicioCambiada()));
    connect(ui->dtFechaFinal, SIGNAL(dateChanged(QDate)), this, SLOT(fechaFinalCambiada()));
    connect(ui->btDetalles, SIGNAL(clicked(bool)), dlgdetalles, SLOT(show()));

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

    if (!ui->txtPapa->text().isEmpty()){
        idx = m_papas_completer->model()->index(m_papas_completer->currentIndex().row(), 0);
        if (idx.isValid())
            papa_id = idx.data().toInt();
    }

    if (persona_id == 0 || diocesis_id == 0){
        int ret = QMessageBox::warning(this, "Faltan datos",
                                       "Faltan datos: los campos persona, diócesis y papa son obligatorios.");
        return;
    }

    QString duracion = ui->txtDuracion->text();
    bool circa_fecha = ui->ckFechaAprox->isChecked();
    bool volver_mirar = ui->ckVolverMirar->isChecked();
    bool fin_muerte = ui->ckFinPorMuerte->isChecked();
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
                  "date_nomination, circa_date_nomination, date_end, duration, end_bydeath, see_again, other_data) "
                  "VALUES(:persona, :diocesis, :papa, "
                  ":fecha_inicio, :circa_fecha, :fecha_final, :duracion, :finpormuerte, :volveramirar, :otrosdatos)");
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
        borrarCampos();
    }
    else {
        int ret = QMessageBox::warning(this, "Error",
                                       "Ha habido un error al ejecutar la consulta de inserción.");
        return;
    }

}

void dlgNuevoObispo::anadirPersona()
{
    dlgSeleccionarGeneral *seleccionar = new dlgSeleccionarGeneral(PERSONA, this);
    seleccionar->show();

    connect(seleccionar, SIGNAL(personaEscogidaSignal(Persona)), this, SLOT(recibirPersona(Persona)));
}

void dlgNuevoObispo::anadirDiocesis()
{
    dlgSeleccionarGeneral *seleccionar = new dlgSeleccionarGeneral(DIOCESIS, this);
    seleccionar->show();

    connect(seleccionar, SIGNAL(diocesisEscogidaSignal(Diocesis)), this, SLOT(recibirDiocesis(Diocesis)));
}

void dlgNuevoObispo::anadirFuente()
{
    dlgFuenteEntrada *fuente = new dlgFuenteEntrada(this);
    fuente->show();

    connect(fuente, SIGNAL(signalFuente(fuente)), this, SLOT(recibirFuente(fuente)));
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
        query.exec();
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