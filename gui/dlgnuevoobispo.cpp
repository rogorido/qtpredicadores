#include "dlgnuevoobispo.h"
#include "ui_dlgnuevoobispo.h"

#include <QSqlQueryModel>
#include <QCompleter>

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
    m_papas->setQuery("SELECT pope_id, pope_name FROM general.popes ORDER BY pope_name");

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
