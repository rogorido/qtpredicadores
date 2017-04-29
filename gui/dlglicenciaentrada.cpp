#include "dlglicenciaentrada.h"
#include "ui_dlglicenciaentrada.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QListWidgetItem>

const QString sql_otorgantes="SELECT DISTINCT details->>'otorgante' AS otorgante "
                             "FROM resolutions_details WHERE details->>'otorgante' IS NOT NULL "
                             "ORDER BY otorgante;";
const QString sql_tipo="SELECT DISTINCT details->>'tipo' AS tipo "
                       "FROM resolutions_details WHERE details ? 'licencia' ORDER BY tipo;";

const QString sql_receptores="SELECT DISTINCT details->>'receptor' AS receptor "
                             "FROM resolutions_details WHERE details->>'receptor' IS NOT NULL "
                             "ORDER BY receptor";

dlgLicenciaEntrada::dlgLicenciaEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgLicenciaEntrada)
{
    ui->setupUi(this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->txtOtorgante, SIGNAL(returnPressed()), this, SLOT(anadirOtorgante()));

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
    if (!ui->txtOtorgante->text().isEmpty()){
        otorgantes.append(ui->txtOtorgante->text());
        QListWidgetItem *item = new QListWidgetItem(ui->txtOtorgante->text(), ui->lwOtorgantes);
    }

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

    tipos_model = new QSqlQueryModel(this);
    tipos_model->setQuery(sql_tipo);

    tipos_completer = new QCompleter(tipos_model, this);
    tipos_completer->setCompletionColumn(0);
    tipos_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtTipo->setCompleter(tipos_completer);

    receptores_model = new QSqlQueryModel(this);
    receptores_model->setQuery(sql_receptores);

    receptores_completer = new QCompleter(receptores_model, this);
    receptores_completer->setCompletionColumn(0);
    receptores_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtReceptor->setCompleter(receptores_completer);
}
