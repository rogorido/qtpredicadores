#include "dlgnuevaresolucion.h"
#include "ui_dlgnuevaresolucion.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QCompleter>
#include <QTableWidget>
#include <QMessageBox>

#include <QJsonValue>
#include <QSqlError>

#include <QDebug>

#include "models/temasmodel.h"
#include "dlgdetalles.h"
#include "objs/jsongestor.h"
#include "gui/dlgtemas.h"
#include "gui/dlgseleccionargeneral.h"

dlgNuevaResolucion::dlgNuevaResolucion(int capitulo,
                                 QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaResolucion), capitulo_origen(capitulo)
{
    ui->setupUi(this);

    jsongestor = new JsonGestor(this);

    dlgdetalles = new dlgDetalles(jsongestor, this);

    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarResolucion()));
    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->txtProvincia, SIGNAL(dobleclicked()), this, SLOT(anadirProvincia()));
    connect(ui->btQuitarProvincia, SIGNAL(clicked()), this, SLOT(quitarProvincia()));

    /*
     * si capitulo !=0 entonces es que venimos del form Capitulos
     */
    if (capitulo > 0)
        origen = true;
}

dlgNuevaResolucion::~dlgNuevaResolucion()
{
    delete ui;
}

void dlgNuevaResolucion::aceptarResolucion(){

    QString resolucion;

    resolucion = ui->txtResolucion->toPlainText();

    if (resolucion.isEmpty()){
        int ret = QMessageBox::warning(this, "No hay texto en la resolución general",
                                       "Introduzca por favor texto en la resolución");
        return;
    }

    QString resolucion_resumen = ui->txtResolucionResumen->toPlainText();
    QString resolucion_trad = ui->txtResolucionTraduccion->toPlainText();
    QString epigrafe = ui->txtEpigrafe->text();
    QString notas = ui->txtResolucionNotas->toPlainText();
    int interesante = ui->spInteresante->value();
    bool entendida = ui->chEntendida->checkState();
    bool volveramirar = ui->chVolverMirar->checkState();
    bool traducida = ui->chTradudida->checkState();

    QSqlQuery query;


    if (query.exec()){

      //QSqlQuery lastid("select currval('capitulos_capitulo_id_seq')");
      QSqlQuery lastid("select max(resolution_id) from resolutions");

      lastid.first();
      int id = lastid.value(0).toInt();

      qDebug() << "El valor del capitulo es: " << id;

      introducirJson(id);
      introducirTemas(id);
    }
}

void dlgNuevaResolucion::introducirJson(const int id){

    QSqlQuery query;
    int totaljson;

    jsongestor->actualizarPrevioIntroducir();
    totaljson = jsongestor->getSize();

    if (totaljson == 0)
        return;

    for (int var = 0; var < totaljson; ++var) {

        QString jsonfinal = jsongestor->getJsonString(var);

        query.prepare("INSERT INTO resolutions_details(resolution_id, details) VALUES(:resolucionid, :json)");
        query.bindValue(":resolucionid", id);
        query.bindValue(":json", jsonfinal);
        query.exec();
    }
}

void dlgNuevaResolucion::introducirTemas(const int id){

    if (temas_lista.size() == 0)
        return;

    for (int i = 0; i < temas_lista.size(); ++i) {

        QSqlQuery query;
        query.prepare("INSERT INTO themes_resolutions(theme_id, resolution_id) VALUES (:tema, :resolucion)");
        query.bindValue(":tema", temas_lista.at(i).id);
        query.bindValue(":resolucion", id);
        query.exec();
    }

}

void dlgNuevaResolucion::on_btDetalles_clicked()
{
    dlgdetalles->show();
}

void dlgNuevaResolucion::on_btTemas_clicked(){

    dlgTemas *dlgtemas = new dlgTemas(this);

    dlgtemas->show();

    connect(dlgtemas, SIGNAL(temasSeleccionadosSignal(QList<elementopareado>)), this, SLOT(recibirTemas(QList<elementopareado>)));
}

void dlgNuevaResolucion::recibirTemas(QList<elementopareado> temas){

    temas_lista = temas;
}

void dlgNuevaResolucion::anadirProvincia(){

    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(PROVINCIA, this);

    dlgseleccionar->show();
    connect(dlgseleccionar, SIGNAL(provinciaEscogidaSignal(Provincia)), this, SLOT(recibirProvincia(Provincia)));
}

void dlgNuevaResolucion::recibirProvincia(Provincia provincia){

    provincia_id = provincia.getId();

    ui->txtProvincia->setText(provincia.getNombre());
}

void dlgNuevaResolucion::quitarProvincia(){

    provincia_id = 0;
    ui->txtProvincia->setText("");
}
