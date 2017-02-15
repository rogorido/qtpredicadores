#include "nuevaresolucion.h"
#include "ui_nuevaresolucion.h"

#include <QInputDialog>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QTableWidget>

#include <QDebug>

#include "temas.h"
#include "lugares.h"
#include "personas.h"
#include "casas.h"

NuevaResolucion::NuevaResolucion(Temas *temas,
                                 Lugares *lugares,
                                 Personas *personas,
                                 Casas *casas,
                                 QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevaResolucion), m_temas(temas), m_lugares(lugares), m_personas(personas), m_casas(casas)
{
    ui->setupUi(this);

    rellenarCombos();

    connect(ui->btNuevoJson, SIGNAL(clicked()), this, SLOT(nuevoJson()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarResolucion()));

    QTreeWidgetItem *itemnivelcero = new QTreeWidgetItem(ui->treeDetalles);
    /*
     * realmente esto es una cutrada.. habría que ponerlo solo si
     * hay algo, pero bueno, ya lo corregiré...
     */
    itemnivelcero->setText(0, "Datos 0");

    /*
     * convertimos el QtreeWidgetItem que acabamos de meter
     * en el "activo" al que tienen que ir los children
     */
    nivelactivo = new QTreeWidgetItem();
    nivelactivo = itemnivelcero;
}

NuevaResolucion::~NuevaResolucion()
{
    delete ui;
}

void NuevaResolucion::rellenarCombos(){

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

void NuevaResolucion::on_btNuevoTema_clicked(){

    QString tema;

    tema = QInputDialog::getText(this, "Introduzca nuevo tema", "Nueva tema");

    if (!tema.isEmpty())
        m_temas->AnadirTema(tema);

}

void NuevaResolucion::on_btAnadirTema_clicked(){
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

void NuevaResolucion::on_btQuitarTema_clicked(){

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

void NuevaResolucion::on_btJsonAnadirDescripcion_clicked(){

    QString valor = ui->cboDescripcion->currentText();

    if (!valor.isEmpty()){
        jsondetalles.insert("Tipo", valor);
        anadirTreeChildItem("Tipo", valor);
    }

}

void NuevaResolucion::on_btJsonAnadirLugar_clicked(){
    QString valor = ui->cboLugares->currentText();

    if (!valor.isEmpty()){
        jsondetalles.insert("Lugar", valor);
        anadirTreeChildItem("Lugar", valor);
    }

}

void NuevaResolucion::on_btJsonAnadirPersona_clicked(){

    QString valor = ui->cboPersonas->currentText();

    if (!valor.isEmpty()){
        jsondetalles.insert("Persona", valor);
        anadirTreeChildItem("Persona", valor);
    }

}

void NuevaResolucion::nuevoJson(){
    /*
     * esto se llama cuando queremos meter otro bloque
     * de datos en json
     */

    /*
     * en ppo lo primero que hacemos es comprobar si
     * jsondetalles está vacío pues si no lo está quiere decir
     * que ya hemos estado metiendo cosas SIN pasarlas a
     * jsondetalles_lista...
     * pero tiene que haber una manera mejor!
     */

    if (!jsondetalles.isEmpty())
        jsondetalles_lista.append(jsondetalles);

    jsondetalles.clear();

    QTreeWidgetItem *itemnivelcero = new QTreeWidgetItem(ui->treeDetalles);
    int nivel = jsondetalles_lista.count();
    itemnivelcero->setText(0, QString("Datos %1").arg(nivel));

    nivelactivo = itemnivelcero;
}

void NuevaResolucion::aceptarResolucion(){

    generarJson();

}

void NuevaResolucion::generarJson(){
    QString json;
    QSqlQuery query;

    /*
     * ponemos esto pq si hay un jsondetalles que no se ha metido
     * se perdería, pero hay que encontrar un sistema mejor
     */
    if (!jsondetalles.isEmpty())
        jsondetalles_lista.append(jsondetalles);

    for (int var = 0; var < jsondetalles_lista.size(); ++var) {

        /*
         * metemos en una variable temporal el QMultiMap
         * correspondiente a este elemento de la lista
         */
        QMultiMap<QString, QVariant> jsontemporal;
        jsontemporal = jsondetalles_lista.at(var);

        json = "{";

        QMapIterator<QString, QVariant> i(jsontemporal);
        while (i.hasNext()) {
            i.next();
            json += "\"" + i.key() + "\" : \"" + i.value().toString() + "\", ";
        }

        json.chop(2);
        json += "}";

        query.prepare("INSERT INTO resoluciones_detalles(resolucion_id, detalle) VALUES(1, :json)");
        query.bindValue(":json", json);
        query.exec();
    }
}

void NuevaResolucion::anadirTreeChildItem(const QString key, const QString value){

    QTreeWidgetItem *itemniveluno = new QTreeWidgetItem();
    itemniveluno->setText(0, key);
    itemniveluno->setText(1, value);
    nivelactivo->addChild(itemniveluno);

}


