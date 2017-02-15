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

    //qDebug() << "Entradas: " << int(jsondetalles.count());

}

void NuevaResolucion::on_btJsonAnadirLugar_clicked(){
    QString valor = ui->cboLugares->currentText();

    jsondetalles.insert("Lugar", valor);

    //qDebug() << "Entradas: " << int(jsondetalles.count());

}
