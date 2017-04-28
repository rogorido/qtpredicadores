#include "dlgmasivo.h"
#include "ui_dlgmasivo.h"

#include <QSqlQuery>
#include <QSqlTableModel>
#include <QModelIndex>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>

#include "objs/jsongestor.h"

#include <QDebug>

/*
 * en teoría todo eso de seleccionar provincias, etc.
 * habría que hacerlo con un QSortFilterProxyModel pero
 * el cabrón me da problemas pq me da un crash de lo más
 * errático, que creo que no es culpa de mi código.
 * Por eso lo hago a mano con un QList<elementopareado>
 */

dlgMasivo::dlgMasivo(int chapter, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgMasivo), chapterescogido(chapter)
{
    ui->setupUi(this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->btAnadirProvincia, SIGNAL(clicked(bool)), this, SLOT(anadirProvincia()));
    connect(ui->btQuitarProvincia, SIGNAL(clicked(bool)), this, SLOT(quitarProvincia()));

    desmarcarTodasProvincias();
    cargarModelos();
}

dlgMasivo::~dlgMasivo()
{
    delete ui;
}

void dlgMasivo::aceptar()
{
    if (ui->txtKey->text().isEmpty() || ui->txtValue->text().isEmpty()){
        int ret = QMessageBox::warning(this, "Imposible al introducir los datos",
                                       "Los campos key y value son obligatorios.");
        return;
    }

    if (provinciasescogidas.size() == 0) {
        int ret = QMessageBox::warning(this, "No hay provincias escogidas",
                                       "No hay provincias escogidas.");
        return;
    }

    QString key = ui->txtKey->text();
    QString valor = ui->txtValue->text();

    /*
     * la verdad es que hago un lío del carajo que no sé si
     * es necesario, pues uso QJsonDocuments, etc. para todo
     * esto cuando tal vez podría construir yo mismo el QString
     * para el json de postgresql. En cualquier caso: lo de usar
     * finalmente un QJsonDocument es pq permite pasarlo a un QString.
     */
    for (int i = 0; i < provinciasescogidas.size(); ++i) {
        QJsonObject json;

        json.insert(key, valor);
        json.insert("Provincia", QJsonValue(provinciasescogidas.at(i).id));

        QJsonDocument jsondoc(json);
        QString jsonfinal = jsondoc.toJson(QJsonDocument::Compact);

        QSqlQuery query;
        query.prepare("INSERT INTO chapters.chapters_details(chapter_id, details) VALUES(:id, :detalles)");
        query.bindValue(":id", chapterescogido);
        query.bindValue(":detalles", jsonfinal);
        query.exec();
    }

    close();

}

void dlgMasivo::anadirProvincia()
{

    QModelIndex idx = provincias->index(ui->twProvinciasSinSeleccionar->currentIndex().row(), 0);
    QModelIndex idxnombre = provincias->index(ui->twProvinciasSinSeleccionar->currentIndex().row(), 1);

    if (!idx.isValid() || !idxnombre.isValid())
        return;

    int id_prov = provincias->data(idx, Qt::DisplayRole).toInt();
    QString nombre = provincias->data(idxnombre, Qt::DisplayRole).toString();

    elementopareado nuevo;
    nuevo.id = id_prov;
    nuevo.elemento = nombre;

    provinciasescogidas.append(nuevo);

    /* añadimos un elem a la tabla */
    QListWidgetItem *item = new QListWidgetItem(nuevo.elemento, ui->twProvinciasSeleccionadas);

}

void dlgMasivo::quitarProvincia()
{

}

void dlgMasivo::desmarcarTodasProvincias()
{
    /*
     * con esto desmacamos todas las provincias que
     * pudieran estar marcadas al principio.
     */

    QSqlQuery query;

    query.exec("UPDATE provinces SET selected=FALSE");

}

void dlgMasivo::cargarModelos()
{
    provincias = new QSqlTableModel(this);
    provincias->setTable("general.provinces");
    provincias->select();
    provincias->sort(1, Qt::AscendingOrder);
    //provincias->setEditStrategy(QSqlTableModel::OnRowChange);

    ui->twProvinciasSinSeleccionar->setModel(provincias);

    // esto es para hacer el loop de un array de ints...
    // la finalidad: ocultar algunas columnas
    std::vector<int> v = {0, 2, 3, 4, 5, 6, 7, 8};
    for(int n : v) {
        ui->twProvinciasSinSeleccionar->hideColumn(n);
        }

    ui->twProvinciasSinSeleccionar->setAlternatingRowColors(true);
    ui->twProvinciasSinSeleccionar->resizeColumnsToContents();
    ui->twProvinciasSinSeleccionar->resizeRowsToContents();
    ui->twProvinciasSinSeleccionar->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twProvinciasSinSeleccionar->setSelectionMode(QAbstractItemView::SingleSelection);


}
