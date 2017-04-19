#include "dlgnuevocapitulo.h"
#include "ui_dlgnuevocapitulo.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QSqlQuery>

#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>

#include "models/lugaresmodel.h"
#include "models/capitulosmodel.h"
#include "gui/dlgnuevolugar.h"
#include "gui/dlgseleccionargeneral.h"
#include "objs/capitulo.h"

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
    m_capitulos = CapitulosModel::InstanceModel();

    lugar_query = new QSqlQueryModel(this);
    lugar_completer = new QCompleter(this);
    cargarCompleters();

    QDate fechainicial = QDate(1500, 1, 1);

    ui->dtInicial->setMinimumDate(fechainicial);
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

    Capitulo *capitulo = new Capitulo();

    QString titulogeneral = ui->txtNombreGeneral->text();

    int lugar = lugarescogido_struct.id;
    int maestrogeneral = maestrogeneral_struct.id;;
    QString tipo = ui->cboTipoCapitulo->currentText();
    QDate fechainicial;
    QDate fechafinal;
    //QDate fechainicial;
    //QDate fechafinal;
    QString tomo = ui->txtTomo->text();
    QString paginas = ui->txtPaginas->text();
    QString notas = ui->txtNotas->toPlainText();
    QString asistentes = ui->txtAsistentes->toPlainText();

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

    capitulo->setNombre(titulogeneral);
    capitulo->setLugar(lugar);
    capitulo->setTipo(tipo);
    capitulo->setMaestroGeneral(maestrogeneral);
    capitulo->setVolumen(tomo);
    capitulo->setPaginas(paginas);
    capitulo->setAsistentes(asistentes);
    capitulo->setNotas(notas);
    capitulo->setFechaInicio(fechainicial);
    capitulo->setFechaFin(fechafinal);

    if (m_capitulos->AnadirCapitulo(capitulo)) {
        borrarCampos();
    }
    else {
        int ret = QMessageBox::warning(this, "Error al introducir la resolución",
                                       "Error al introducir la resolución en la BD");
        return;
    }

}

void dlgNuevoCapitulo::cargarCompleters(){

    /*
     * TODO: esto entiendo que se puede cambiar al nuevo
     *  clase Lugares que tengo...
     * TODO: entiendo q esto ya no lo uso, no?
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

void dlgNuevoCapitulo::borrarCampos(){

    ui->txtNombreGeneral->setText("");
    ui->txtLugar->setText("");
    ui->txtMaestroGeneral->setText("");
    ui->txtPaginas->setText("");
    ui->txtTomo->setText("");
    ui->txtNotas->clear();
    ui->txtAsistentes->clear();

    maestrogeneral_struct = elementopareado();
    lugarescogido_struct = elementopareado();

}
