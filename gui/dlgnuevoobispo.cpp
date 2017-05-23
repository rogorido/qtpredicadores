#include "dlgnuevoobispo.h"
#include "ui_dlgnuevoobispo.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QCompleter>
#include <QMessageBox>
#include <QDebug>

#include "objs/obispo.h"
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

    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarObispo()));
    connect(ui->btFuente, SIGNAL(clicked()), this, SLOT(anadirFuente()));
    connect(ui->txtPersona, SIGNAL(dobleclick()), this, SLOT(anadirPersona()));
    connect(ui->txtDiocesis, SIGNAL(dobleclick()), this, SLOT(anadirDiocesis()));
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

    idx = m_papas_completer->model()->index(m_papas_completer->currentIndex().row(), 0);
    papa_id = idx.data().toInt();

    if (persona_id == 0 || diocesis_id == 0 || papa_id == 0){
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
     * TODO: faltaría lo de other_data, que es difernete de lo que
     * está en la tabla bishops_details...
     */
    query.prepare("INSERT INTO bishops.bishops(bishop_person_id, diocese_id, pope_id, "
                  "date_nomination, circa_date_nomination, date_end, duration, end_bydeath, see_again) "
                  "VALUES(:persona, :diocesis, :papa, "
                  ":fecha_inicio, :circa_fecha, :fecha_final, :duracion, :finpormuerte, :volveramirar)");
    query.bindValue(":persona", persona_id);
    query.bindValue(":diocesis", diocesis_id);
    query.bindValue(":papa", papa_id);

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

    if (query.exec()){
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
    fuente_recibida = true;

    fuentedatos->insert("book", QJsonValue(datoobra.titulo));
    fuentedatos->insert("volume", datoobra.tomo);
    fuentedatos->insert("pages", datoobra.paginas);
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

    ui->txtPersona->setFocus();
}
