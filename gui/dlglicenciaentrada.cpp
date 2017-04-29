#include "dlglicenciaentrada.h"
#include "ui_dlglicenciaentrada.h"

#include <QSqlQueryModel>
#include <QCompleter>

const QString sql_otorgantes="SELECT DISTINCT details->>'otorgante' AS otorgante "
                             "FROM resolutions_details WHERE details->>'otorgante' IS NOT NULL "
                             "ORDER BY otorgante;";

dlgLicenciaEntrada::dlgLicenciaEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgLicenciaEntrada)
{
    ui->setupUi(this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));

    cargarModelos();
}

dlgLicenciaEntrada::~dlgLicenciaEntrada()
{
    delete ui;
}

void dlgLicenciaEntrada::aceptar()
{
    licencia_activa.setLicenciaTipo(ui->txtTipo->text());
    licencia_activa.setOtorgantes(otorgantes);
    licencia_activa.setReceptores(receptores);
    licencia_activa.setAsunto(ui->txtAsunto->text());
    licencia_activa.setSeguridad(ui->spSeguridad->value());

    emit(aceptarLicencia(licencia_activa));

    close();
}

void dlgLicenciaEntrada::anadirReceptor()
{

}

void dlgLicenciaEntrada::quitarReceptor()
{

}

void dlgLicenciaEntrada::anadirOtorgante()
{

}

void dlgLicenciaEntrada::quitarOtorgante()
{

}

void dlgLicenciaEntrada::cargarModelos()
{

    otorgantes_model = new QSqlQueryModel(this);
    otorgantes_model->setQuery(sql_otorgantes);

    otorgantes_completer = new QCompleter(otorgantes_model, this);
    otorgantes_completer->setCompletionColumn(0);
    otorgantes_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtOtorgante->setCompleter(otorgantes_completer);
}
