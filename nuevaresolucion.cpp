#include "nuevaresolucion.h"
#include "ui_nuevaresolucion.h"

#include <QInputDialog>
#include <QSqlRecord>
#include <QTableWidget>

#include <QDebug>

#include "temas.h"
#include "lugares.h"

NuevaResolucion::NuevaResolucion(Temas *temas, Lugares *lugares, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevaResolucion), m_temas(temas), m_lugares(lugares)
{
    ui->setupUi(this);

    rellenarCombos();

    connect(ui->btNuevoJson, SIGNAL(clicked()), this, SLOT(nuevoJson()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarResolucion()));
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

    jsondetalles.insert("Tipo", valor);

    qDebug() << "Entradas: " << int(jsondetalles.count());
    qDebug() << "JSONs: " << int(jsondetalles_lista.count());
}

void NuevaResolucion::on_btJsonAnadirLugar_clicked(){
    QString valor = ui->cboLugares->currentText();

    jsondetalles.insert("Lugar", valor);

    qDebug() << "Entradas: " << int(jsondetalles.count());
    qDebug() << "JSONs: " << int(jsondetalles_lista.count());

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
}

void NuevaResolucion::aceptarResolucion(){

    generarJson();

}

void NuevaResolucion::generarJson(){
    QString json;

    /*
     * ponemos esto pq si hay un jsondetalles que no se ha metido
     * se perdería, pero hay que encontrar un sistema mejor
     */
    nuevoJson();

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
        json += "}";

        qDebug() << "Este es json: " << json;
    }
}




