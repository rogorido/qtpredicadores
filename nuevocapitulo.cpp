#include "nuevocapitulo.h"
#include "ui_nuevocapitulo.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QSqlQuery>

#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>

/*
#include <QSqlRecord>
#include <QSqlQuery>
*/

NuevoCapitulo::NuevoCapitulo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevoCapitulo)
{
    ui->setupUi(this);

    connect(ui->btCancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarCapitulo()));

    ui->dtFinal->calendarPopup();

    ui->cboTipoCapitulo->addItem("General");
    ui->cboTipoCapitulo->addItem("Provincial");
    ui->cboTipoCapitulo->setCurrentIndex(-1);

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
    QString lugar;
    QString maestrogeneral;
    QString tipo;
    QDate fechainicial;
    QDate fechafinal;
    QString tomo;
    QString paginas;
    QString notas;
    QString asistentes;

    titulogeneral = ui->txtNombreGeneral->text();

    /* vamos extrayendo todos los datos */
    (!ui->txtLugar->text().isEmpty()) ?
                lugar = ui->txtLugar->text() : lugar = "";

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

    fechainicial = ui->dtInicial->date();
    fechafinal = ui->dtFinal->date();


    QSqlQuery query;
    //query.prepare("INSERT INTO capitulos(nombregeneral, lugar, fechainicio, fechafinal, tipo, maestrogeneral, asistentes, tomo, paginas, notas) "
      //            "VALUES(:nombre, :lugar, :fechainicio, :fechafinal, :tipo, :maestro, :asistentes, :tomo, :paginas, :notas)" );
    query.prepare("INSERT INTO capitulos(nombregeneral, lugar, tipo, maestrogeneral, asistentes, tomo, paginas, notas) "
                  "VALUES(:nombre, :lugar, :tipo, :maestro, :asistentes, :tomo, :paginas, :notas)" );
    query.bindValue(":nombre", titulogeneral);
    query.bindValue(":lugar", 1);
    query.bindValue(":tipo", tipo);
    query.bindValue(":maestro", maestrogeneral);
    query.bindValue(":asistentes", asistentes);
    //query.bindValue(":fechainicio", fechainicial);
    //query.bindValue(":fechafinal", fechafinal);
    query.bindValue(":tomo", tomo);
    query.bindValue(":paginas", paginas);
    query.bindValue(":notas", notas);

    if (query.exec()){
        qDebug("Titulo: " + titulogeneral.toUtf8());
        //qDebug("EXECUTED "+query.executedQuery().toAscii());
        qDebug("EXECUTED "+query.executedQuery().toUtf8());
        //qDebug("ultimo error: " + query.lastError().toUtf8);
    }

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

