#include "dlgtemas.h"
#include "ui_dlgtemas.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QMdiSubWindow>
#include <QTableWidget>
#include <QDebug>

#include "objs/tema.h"
#include "widgets/myqmdiarea.h"

dlgTemas::dlgTemas(QList<elementopareado> *temas_lista, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgTemas), temas(temas_lista)
{
    ui->setupUi(this);

    mdiarea = MyQmdiArea::Instance(this);

    ui->twTemas->setAlternatingRowColors(true);
    ui->twTemas->resizeColumnsToContents();
    ui->twTemas->resizeRowsToContents();
    ui->twTemas->setHorizontalHeaderLabels(QStringList("Temas"));
    ui->twTemas->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twTemas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twTemas->horizontalHeader()->setStretchLastSection(true);

    // los dos hacen lo mismo... tvz quitar uno
    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(cerrar()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(cerrar()));

    inicializarTemasWidget();

}

dlgTemas::~dlgTemas()
{
    delete ui;
}

void dlgTemas::on_btAnadirTema_clicked(){

    dlgseleccionar = new dlgSeleccionarGeneral(TEMA, this);
    connect(dlgseleccionar, SIGNAL(temaEscogidoSignal(Tema)), this, SLOT(recibirTema(Tema)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgseleccionar);
    window->show();

}

void dlgTemas::recibirTema(Tema tema){

    /* creamos un nuevo struct y lo añadimos a la lista */
    elementopareado nuevo;
    nuevo.id = tema.getId();
    nuevo.elemento = tema.getTema();

    qDebug() << "ehmos recibido el tema...";

    temas->append(nuevo);

    meterTemaWidget(nuevo.elemento);

}

void dlgTemas::cerrar()
{
    parentWidget()->close();
}

void dlgTemas::meterTemaWidget(QString tema)
{
    /* añadimos un elem a la tabla */
    QTableWidgetItem *item = new QTableWidgetItem(tema);
    //this will give the present number of rows available.
    int insertRow = ui->twTemas->rowCount();
    //insert the row at the bottom of the table widget - using.
    ui->twTemas->insertRow(insertRow);

    ui->twTemas->setItem(insertRow, 0, item);

    ui->twTemas->resizeColumnsToContents();
    ui->twTemas->resizeRowsToContents();
}

void dlgTemas::inicializarTemasWidget()
{
    if (temas->size() > 0) {
        for (int i = 0; i < temas->size(); ++i) {
            meterTemaWidget(temas->at(i).elemento);
          }
     }
}

void dlgTemas::on_btQuitarTema_clicked(){

    QModelIndex idx = ui->twTemas->currentIndex();

    if (!idx.isValid())
        return;

    QString valor = idx.data().toString();

    int row = ui->twTemas->currentRow();
    ui->twTemas->removeRow(row);

    for (int i = 0; i < temas->size(); ++i) {
      if(temas->at(i).elemento == valor){
        temas->removeAt(i);
        break;
      }
     }
}

/*
void dlgTemas::aceptarTemas(){
    emit(temasSeleccionadosSignal(temas_lista));

    this->hide();
}
*/
