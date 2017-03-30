#include "dlgnuevocapitulo.h"
#include "ui_dlgnuevocapitulo.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QSqlQuery>

#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>

#include "models/lugaresmodel.h"
#include "gui/dlgnuevolugar.h"
#include "gui/dlgseleccionargeneral.h"

dlgNuevoCapitulo::dlgNuevoCapitulo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevoCapitulo)
{
    ui->setupUi(this);

    connect(ui->btCancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarCapitulo()));
    connect(ui->dtInicial, SIGNAL(dateChanged(const QDate)), this, SLOT(fechaInicialCambiada()));
    connect(ui->dtFinal, SIGNAL(dateChanged(const QDate)), this, SLOT(fechaFinalCambiada()));
    connect(ui->btQuitarLugar, SIGNAL(clicked()), this, SLOT(quitarLugar()));
    connect(ui->txtMaestroGeneral, SIGNAL(dobleclick()), this, SLOT(anadirMaestroGeneral()));
    connect(ui->txtLugar, SIGNAL(dobleclick()), this, SLOT(anadirLugar()));

    ui->dtFinal->calendarPopup();

    ui->cboTipoCapitulo->addItem("General");
    ui->cboTipoCapitulo->addItem("Provincial");
    ui->cboTipoCapitulo->setCurrentIndex(-1);

    bFechaInicialModificada = false;
    bFechaFinalModificada = false;

    m_lugares = LugaresModel::InstanceModel();

    lugar_query = new QSqlQueryModel(this);
    lugar_completer = new QCompleter(this);
    cargarCompleters();
}

dlgNuevoCapitulo::~dlgNuevoCapitulo()
{
    delete ui;
}

void dlgNuevoCapitulo::aceptarCapitulo(){

    if (ui->txtNombreGeneral->text().isEmpty()){
        int ret = QMessageBox::warning(this, "No hay título general", "Introduzca por favor un título general");
        return;
    }

    QString titulogeneral;
    /*
     * Atención: lugar es QVariant pq eso permite que sea NULL
     * que es lo que hace falta cuando no hay una ciudad
     */
    QVariant lugar;
    int maestrogeneral;
    QString tipo;
    QVariant fechainicial;
    QVariant fechafinal;
    //QDate fechainicial;
    //QDate fechafinal;
    QString tomo;
    QString paginas;
    QString notas;
    QString asistentes;

    titulogeneral = ui->txtNombreGeneral->text();

    /* vamos extrayendo todos los datos */

    if (!ui->txtMaestroGeneral->text().isEmpty())
                maestrogeneral = maestrogeneral_struct.id;

    (!ui->txtPaginas->text().isEmpty()) ?
                paginas = ui->txtPaginas->text() : paginas = "";

    (!ui->txtAsistentes->toPlainText().isEmpty()) ?
                asistentes = ui->txtAsistentes->toPlainText() : asistentes = "";

    (!ui->txtTomo->text().isEmpty()) ?
                tomo = ui->txtTomo->text() : tomo = "";

    (!ui->txtNotas->toPlainText().isEmpty()) ?
                notas = ui->txtNotas->toPlainText() : notas ="";

    (!ui->cboTipoCapitulo->currentText().isEmpty()) ?
                tipo = ui->cboTipoCapitulo->currentText() : tipo = "";

    /*
     * si la fecha ha cambiado, meteremos la fecha
     * y para ello lo transformamos (entiendo que implícitamente)
     * de un QVariant (que estaría NULL) a un QDate
     */
    if (bFechaInicialModificada){
        fechainicial = ui->dtInicial->date();
    }

    if (bFechaFinalModificada){
        fechafinal = ui->dtFinal->date();
    }

    if (!ui->txtLugar->text().isEmpty()){
                lugar = lugarescogido_struct.id;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO chapters.chapters(general_name, place_id, date_beginning, date_ending, "
                  "type_chapter, general_master, attendees, volume, pages, notes) "
                  "VALUES(:nombre, :lugar_id, :fechainicio, :fechafinal, "
                  ":tipo, :maestro, :asistentes, :tomo, :paginas, :notas)");
    query.bindValue(":nombre", titulogeneral);
    query.bindValue(":lugar_id", lugar);
    query.bindValue(":tipo", tipo);
    query.bindValue(":maestro", maestrogeneral);
    query.bindValue(":asistentes", asistentes);
    query.bindValue(":fechainicio", fechainicial);
    query.bindValue(":fechafinal", fechafinal);
    query.bindValue(":tomo", tomo);
    query.bindValue(":paginas", paginas);
    query.bindValue(":notas", notas);
    query.exec();

}

void dlgNuevoCapitulo::cargarCompleters(){

    /*
     * TODO: esto entiendo que se puede cambiar al nuevo
     *  clase Lugares que tengo...
     */
    lugar_query->setQuery("SELECT DISTINCT lugar FROM lugares WHERE lugar IS NOT NULL ORDER BY lugar");

    lugar_completer->setModel(lugar_query);
    lugar_completer->setCompletionColumn(0);
    lugar_completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->txtLugar->setCompleter(lugar_completer);

}

int dlgNuevoCapitulo::extraerLugar(QString lugar){
    /*
     * Extraemos de la table lugares el id del
     * lugar escogido. Probablemente habría que
     * hacerlo mejor con un modelo o algo...
     */

    int valor;

    QSqlQuery query(QString("SELECT lugar_id FROM lugares WHERE lugar='%1'").arg(lugar));
    query.first();

    valor = query.value(0).toInt();

    return valor;

}

void dlgNuevoCapitulo::fechaInicialCambiada(){
    // cuando cambia la fecha activamos esto para que luego la meta en la base de datos
    bFechaInicialModificada = true;

}

void dlgNuevoCapitulo::fechaFinalCambiada(){
    // cuando cambia la fecha activamos esto para que luego la meta en la base de datos
    bFechaFinalModificada = true;

}

void dlgNuevoCapitulo::anadirLugar(){

    dlgSeleccionarGeneral *dlgSeleccionar = new dlgSeleccionarGeneral(LUGAR, this);
    dlgSeleccionar->show();

    connect(dlgSeleccionar, SIGNAL(lugarEscogidoSignal(Lugar)), this, SLOT(actualizarLugar(Lugar)));

}

void dlgNuevoCapitulo::actualizarLugar(Lugar lugar){

    lugarescogido_struct.id = lugar.getId();
    lugarescogido_struct.elemento = lugar.getLugar();

    ui->txtLugar->setText(lugarescogido_struct.elemento);
}

void dlgNuevoCapitulo::quitarLugar(){
    lugarescogido_struct = elementopareado();
    ui->txtLugar->setText("");
}

void dlgNuevoCapitulo::anadirMaestroGeneral(){

    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(PERSONA, this);

    dlgseleccionar->show();

    connect(dlgseleccionar, SIGNAL(personaEscogidaSignal(Persona)), this, SLOT(recibirMaestroGeneral(Persona)));
}

void dlgNuevoCapitulo::recibirMaestroGeneral(Persona persona){

    maestrogeneral_struct.id = persona.getId();
    maestrogeneral_struct.elemento = persona.getNombre() + ' ' + persona.getApellidos();

    ui->txtMaestroGeneral->setText(maestrogeneral_struct.elemento);
}


void dlgNuevoCapitulo::on_btQuitarMaestroGeneral_clicked(){

    maestrogeneral_struct = elementopareado();
    ui->txtMaestroGeneral->setText("");
}
