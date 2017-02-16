#include "nuevaresolucion.h"
#include "ui_nuevaresolucion.h"

#include <QInputDialog>
#include <QSqlRecord>
#include <QSqlQuery>
//#include <qsqlquerymodel.h>
#include <QCompleter>
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
    cargarModelos();

    connect(ui->btNuevoJson, SIGNAL(clicked()), this, SLOT(nuevoJson()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarResolucion()));
    // señal de que se ha metido un texto en el campo "key" libre
    connect(ui->txtKey, SIGNAL(editingFinished()), this, SLOT(actualizarCompleterValues()));

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

void NuevaResolucion::cargarModelos(){

    /*
     * TODO: tal y como está esto estos completers no se van a actualizar
     * hasta que no se meta algo en la base de datos (bueno, ahora creo que ni con eso)
     * pero no pej cuando vaya metiendo cosas.
     * La posible solución sería pasar los datos del QSqlQueryModel
     * a un QStringList(model?) y añadir luego cosas nuevas a ese modelo
     */

    m_keys = new QSqlQueryModel(this);
    m_keys->setQuery("SELECT DISTINCT json_object_keys(detalle) FROM resoluciones_detalles ORDER BY json_object_keys(detalle);");

    keys_completer = new QCompleter(this);
    keys_completer->setModel(m_keys);
    keys_completer->setCompletionColumn(0);
    keys_completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->txtKey->setCompleter(keys_completer);

    m_values = new QSqlQueryModel(this);
    // ponemos una cosa general que luego habrá que precisar
    m_values->setQuery("SELECT DISTINCT value from resoluciones_detalles, json_each_text(detalle) ORDER BY value;");

    values_completer = new QCompleter(this);
    values_completer->setModel(m_values);
    values_completer->setCompletionColumn(0);
    values_completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->txtValue->setCompleter(values_completer);
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
        /*
         * extraemos el id del combo
         * dado que esto se repite se podría hacer un método
         * al que pasamos el modelo y el combo y devuelve un int
         * pero sinceramente ahora no me acuerdo cómo se hace...
         */
        QSqlRecord record = m_lugares->record(ui->cboLugares->currentIndex());
        int id = record.value(0).toInt();

        jsondetalles.insert("Lugar", id);
        anadirTreeChildItem("Lugar", valor);
    }

}

void NuevaResolucion::on_btJsonAnadirPersona_clicked(){

    QString valor = ui->cboPersonas->currentText();

    if (!valor.isEmpty()){
        /*
         * extraemos el id del combo
         * dado que esto se repite se podría hacer un método
         * al que pasamos el modelo y el combo y devuelve un int
         * pero sinceramente ahora no me acuerdo cómo se hace...
         */
        QSqlRecord record = m_personas->record(ui->cboPersonas->currentIndex());
        int id = record.value(0).toInt();

        jsondetalles.insert("Persona", id);
        anadirTreeChildItem("Persona", valor);
    }

}

void NuevaResolucion::on_btJsonAnadirCasa_clicked(){
    QString valor = ui->cboCasas->currentText();

    if (!valor.isEmpty()){
        /*
         * extraemos el id del combo
         * dado que esto se repite se podría hacer un método
         * al que pasamos el modelo y el combo y devuelve un int
         * pero sinceramente ahora no me acuerdo cómo se hace...
         */
        QSqlRecord record = m_casas->record(ui->cboCasas->currentIndex());
        int id = record.value(0).toInt();

        jsondetalles.insert("Casa", id);
        anadirTreeChildItem("Casa", valor);
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

        json.chop(2); // quitamos la última coma
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

void NuevaResolucion::actualizarCompleterValues(){
    QString key;

    key = ui->txtKey->text();
    m_values->setQuery(QString("SELECT DISTINCT value from resoluciones_detalles, json_each_text(detalle) "
                               "WHERE key='%1' ORDER BY value;").arg(key));


}


