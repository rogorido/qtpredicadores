#include "dlgnuevaresolucion.h"
#include "ui_dlgnuevaresolucion.h"

#include <QInputDialog>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QCompleter>
#include <QTableWidget>
#include <QMessageBox>

#include <QJsonValue>
#include <QSqlError>

#include <QDebug>

#include "models/temasmodel.h"
#include "models/lugaresmodel.h"
#include "models/personasmodel.h"
#include "models/casasmodel.h"

#include "dlgnuevacasa.h"
#include "dlgnuevapersona.h"
#include "dlgdetalles.h"

#include "objs/jsongestor.h"

dlgNuevaResolucion::dlgNuevaResolucion(int capitulo,
                                 QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaResolucion), capitulo_origen(capitulo)
{
    ui->setupUi(this);

    m_temas = TemasModel::InstanceModel();
    m_lugares = LugaresModel::InstanceModel();
    m_casas = CasasModel::InstanceModel();
    m_personas = PersonasModel::InstanceModel();

    jsongestor = new JsonGestor(this);

    dlgdetalles = new dlgDetalles(jsongestor, this);

    rellenarCombos();

    connect(ui->btNuevoJson, SIGNAL(clicked()), this, SLOT(nuevoJson()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarResolucion()));
    // señal de que se ha metido un texto en el campo "key" libre
    connect(ui->txtKey, SIGNAL(editingFinished()), this, SLOT(actualizarCompleterValues()));
    connect(ui->btModificarDetalles, SIGNAL(toggled(bool)), jsongestor, SLOT(modificandoDatos(bool)));


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


void dlgNuevaResolucion::rellenarCombos(){
// TODO: modificar
    ui->cboTemas->setModel(m_temas);
    ui->cboTemas->setCurrentIndex(-1);
    ui->cboTemas->setModelColumn(1);

    ui->cboDescripcion->addItem("Nombramiento");
    ui->cboDescripcion->setCurrentIndex(-1);

    ui->cboLugares->setModel(m_lugares);
    ui->cboLugares->setCurrentIndex(-1);
    ui->cboLugares->setModelColumn(1);

    ui->cboPersonas->setModel(m_personas);
    ui->cboPersonas->setCurrentIndex(-1);
    ui->cboPersonas->setModelColumn(1);

    ui->cboCasas->setModel(m_casas);
    ui->cboCasas->setCurrentIndex(-1);
    ui->cboCasas->setModelColumn(1);

}

void dlgNuevaResolucion::on_btNuevoTema_clicked(){

    QString tema;

    tema = QInputDialog::getText(this, "Introduzca nuevo tema", "Nueva tema");

    if (!tema.isEmpty())
        m_temas->AnadirTema(tema);

}

void dlgNuevaResolucion::on_btAnadirTema_clicked(){
    /* sacamos el record del combobox */

    QSqlRecord record = m_temas->record(ui->cboTemas->currentIndex());
    int id = record.value(0).toInt();
    QString tema = ui->cboTemas->currentText();

    /* creamos un nuevo struct y lo añadimos a la lista */
    elementopareado nuevo;
    nuevo.id = id;
    nuevo.elemento = tema;
    temas_lista.append(nuevo);

    /* añadimos un elem a la tabla */
    QTableWidgetItem *item = new QTableWidgetItem(tema);
    //this will give the present number of rows available.
    int insertRow = ui->twTemas->rowCount();
    //insert the row at the bottom of the table widget - using.
    ui->twTemas->insertRow(insertRow);

    ui->twTemas->setItem(insertRow, 0, item);
}

void dlgNuevaResolucion::on_btQuitarTema_clicked(){

    QString valor = ui->twTemas->currentIndex().data().toString();

    int row = ui->twTemas->currentRow();
    ui->twTemas->removeRow(row);

    for (int i = 0; i < temas_lista.size(); ++i) {
      if(temas_lista.at(i).elemento == valor){
        temas_lista.removeAt(i);
        break;
      }
     }

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

    query.prepare("INSERT INTO resoluciones(resolucion_texto, resolucion_traduccion, resolucion_resumen, capitulo, "
		  "epigrafe, entendida, volveramirar, traducida, interesante, notas) "
		  "VALUES(:resolucion_texto, :resolucion_traduccion, :resolucion_resumen, :capitulo, "
		  ":epigrafe, :entendida, :volveramirar, :traducida, :interesante, :notas)");
    query.bindValue(":resolucion_texto", resolucion);
    query.bindValue(":resolucion_traduccion", resolucion_trad);
    query.bindValue(":resolucion_resumen", resolucion_resumen);
    //query.bindValue(":capitulo", capitulo_origen);
    query.bindValue(":capitulo", 1);
    query.bindValue(":epigrafe", epigrafe);
    query.bindValue(":entendida", entendida);
    query.bindValue(":volveramirar", volveramirar);
    query.bindValue(":traducida", traducida);
    query.bindValue(":interesante", interesante);
    query.bindValue(":notas", notas);

    if (query.exec()){

      //QSqlQuery lastid("select currval('capitulos_capitulo_id_seq')");
      QSqlQuery lastid("select max(resolucion_id) from resoluciones");

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

        query.prepare("INSERT INTO resoluciones_detalles(resolucion_id, detalle) VALUES(:resolucionid, :json)");
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
        query.prepare("INSERT INTO temas_resoluciones(tema_id, resolucion_id) VALUES (:tema, :resolucion)");
        query.bindValue(":tema", temas_lista.at(i).id);
        query.bindValue(":resolucion", id);
        query.exec();
    }

}


void dlgNuevaResolucion::on_btBorrarElemento_clicked()
{

    jsongestor->eliminarElemento();
}

void dlgNuevaResolucion::on_btModificarDetalles_toggled(bool checked)
{
    if (checked){
        ui->btModificarDetalles->setText("Modificando");
    }
    else
        ui->btModificarDetalles->setText("Añadiendo");
}

void dlgNuevaResolucion::on_btDetalles_clicked()
{
    dlgdetalles->show();
}
