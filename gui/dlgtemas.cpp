#include "dlgtemas.h"
#include "ui_dlgtemas.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QTableWidget>

#include "objs/tema.h"

dlgTemas::dlgTemas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgTemas)
{
    ui->setupUi(this);

    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarTemas()));

}

dlgTemas::~dlgTemas()
{
    delete ui;
}

void dlgTemas::on_btAnadirTema_clicked(){

    dlgseleccionar = new dlgSeleccionarGeneral(TEMA, this);
    dlgseleccionar->show();

    connect(dlgseleccionar, SIGNAL(temaEscogidoSignal(Tema)), this, SLOT(recibirTema(Tema)));

}

void dlgTemas::recibirTema(Tema tema){

    /* creamos un nuevo struct y lo añadimos a la lista */
    elementopareado nuevo;
    nuevo.id = tema.getId();
    nuevo.elemento = tema.getTema();
    temas_lista.append(nuevo);

    /* añadimos un elem a la tabla */
    QTableWidgetItem *item = new QTableWidgetItem(nuevo.elemento);
    //this will give the present number of rows available.
    int insertRow = ui->twTemas->rowCount();
    //insert the row at the bottom of the table widget - using.
    ui->twTemas->insertRow(insertRow);

    ui->twTemas->setItem(insertRow, 0, item);
}

void dlgTemas::on_btQuitarTema_clicked(){

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

void dlgTemas::aceptarTemas(){
    emit(temasSeleccionadosSignal(temas_lista));

    this->hide();
}
