#include "nuevocapitulo.h"
#include "ui_nuevocapitulo.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QSqlQuery>

#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>

NuevoCapitulo::NuevoCapitulo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevoCapitulo)
{
    ui->setupUi(this);

    connect(ui->btCancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarCapitulo()));
    connect(ui->dtInicial, SIGNAL(dateChanged(const QDate)), this, SLOT(fechaInicialCambiada()));
    connect(ui->dtFinal, SIGNAL(dateChanged(const QDate)), this, SLOT(fechaFinalCambiada()));

    ui->dtFinal->calendarPopup();

    ui->cboTipoCapitulo->addItem("General");
    ui->cboTipoCapitulo->addItem("Provincial");
    ui->cboTipoCapitulo->setCurrentIndex(-1);

    bFechaInicialModificada = false;
    bFechaFinalModificada = false;

    cargarCompleters();
}

NuevoCapitulo::~NuevoCapitulo()
{
    delete ui;
}

void NuevoCapitulo::aceptarCapitulo(){

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
    QString maestrogeneral;
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

    (!ui->txtMaestroGeneral->text().isEmpty()) ?
                maestrogeneral = ui->txtMaestroGeneral->text() : maestrogeneral = "";

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
                lugar = extraerLugar(ui->txtLugar->text());
    }
    else{
        qDebug("está vacío");
    }

    QSqlQuery query;
    query.prepare("INSERT INTO capitulos(nombregeneral, lugar, fechainicio, fechafinal, tipo, maestrogeneral, asistentes, tomo, paginas, notas) "
                  "VALUES(:nombre, :lugar, :fechainicio, :fechafinal, :tipo, :maestro, :asistentes, :tomo, :paginas, :notas)" );
    query.bindValue(":nombre", titulogeneral);
    query.bindValue(":lugar", lugar);
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

void NuevoCapitulo::cargarCompleters(){

    lugar_query = new QSqlQueryModel(this);
    lugar_query->setQuery("SELECT DISTINCT lugar FROM lugares WHERE lugar IS NOT NULL ORDER BY lugar");

    lugar_completer = new QCompleter(this);
    lugar_completer->setModel(lugar_query);
    lugar_completer->setCompletionColumn(0);
    lugar_completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->txtLugar->setCompleter(lugar_completer);

}

int NuevoCapitulo::extraerLugar(QString lugar){
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

void NuevoCapitulo::fechaInicialCambiada(){
    // cuando cambia la fecha activamos esto para que luego la meta en la base de datos
    bFechaInicialModificada = true;

}

void NuevoCapitulo::fechaFinalCambiada(){
    // cuando cambia la fecha activamos esto para que luego la meta en la base de datos
    bFechaFinalModificada = true;

}
