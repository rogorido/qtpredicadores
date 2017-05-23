#include "dlgnuevoobispo.h"
#include "ui_dlgnuevoobispo.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QCompleter>
#include <QMessageBox>

#include "objs/obispo.h"
#include "dlgseleccionargeneral.h"

dlgNuevoObispo::dlgNuevoObispo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevoObispo)
{
    ui->setupUi(this);

    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarObispo()));
    connect(ui->txtPersona, SIGNAL(dobleclick()), this, SLOT(anadirPersona()));
    connect(ui->txtDiocesis, SIGNAL(dobleclick()), this, SLOT(anadirDiocesis()));

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
                                       "Faltan datos: o bien la persona, o bien la diócesis o bien el papa.");
        return;
    }

    QString duracion = ui->txtDuracion->text();
    QDate fecha_inicio = ui->dtFechaInicio->date();
    QDate fecha_fin = ui->dtFechaFinal->date();
    bool circa_fecha = ui->ckFechaAprox->isChecked();
    bool volver_mirar = ui->ckVolverMirar->isChecked();
    bool fin_muerte = ui->ckFinPorMuerte->isChecked();

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
    query.bindValue(":fecha_inicio", fecha_inicio);
    query.bindValue(":fecha_final", fecha_fin);
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

void dlgNuevoObispo::cargarModelos()
{
    m_papas = new QSqlQueryModel(this);
    m_papas->setQuery("SELECT pope_id, name_pope FROM general.popes ORDER BY name_pope");

    m_papas_completer = new QCompleter(this);
    m_papas_completer->setModel(m_papas);
    m_papas_completer->setCompletionColumn(1);

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

    ui->ckFechaAprox->setCheckState(Qt::Unchecked);
    ui->ckFinPorMuerte->setCheckState(Qt::Unchecked);
    ui->ckVolverMirar->setCheckState(Qt::Unchecked);

    ui->txtPersona->setFocus();
}
