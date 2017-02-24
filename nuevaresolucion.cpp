#include "nuevaresolucion.h"
#include "ui_nuevaresolucion.h"

#include <QInputDialog>
#include <QSqlRecord>
#include <QSqlQuery>
//#include <qsqlquerymodel.h>
#include <QCompleter>
#include <QTableWidget>
#include <QMessageBox>

#include <QJsonDocument>
#include <QJsonValue>
#include <QSqlError>

#include <QDebug>

#include "temasmodel.h"
#include "lugaresmodel.h"
#include "personasmodel.h"
#include "casasmodel.h"

#include "nuevacasa.h"
#include "nuevapersona.h"

#include "jsongestor.h"

NuevaResolucion::NuevaResolucion(int capitulo,
                                 QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevaResolucion), capitulo_origen(capitulo)
{
    ui->setupUi(this);

    m_temas = TemasModel::InstanceModel();
    m_lugares = LugaresModel::InstanceModel();
    m_casas = CasasModel::InstanceModel();
    m_personas = PersonasModel::InstanceModel();

    rellenarCombos();
    cargarModelos();

    connect(ui->btNuevoJson, SIGNAL(clicked()), this, SLOT(nuevoJson()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarResolucion()));
    // señal de que se ha metido un texto en el campo "key" libre
    connect(ui->txtKey, SIGNAL(editingFinished()), this, SLOT(actualizarCompleterValues()));

    jsongestor = new JsonGestor(ui->treeDetalles);

    /*
     * si capitulo !=0 entonces es que venimos del form Capitulos
     */
    if (capitulo > 0)
        origen = true;
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

        jsondetalles["Tipo"]= valor;
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

        jsongestor->anadirValor("Lugar", QJsonValue(valor));

        //jsondetalles["Lugar"] = id;
        //anadirTreeChildItem("Lugar", valor);
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

        jsondetalles["Persona"] = id;
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

        jsondetalles["Casa"]=id;
        anadirTreeChildItem("Casa", valor);
    }
}

void NuevaResolucion::on_btJsonAnadirLibre_clicked(){
    QString key = ui->txtKey->text();
    QString value = ui->txtValue->text();

    if (!key.isEmpty() && !value.isEmpty()){
        jsondetalles[key] = value;
        anadirTreeChildItem(key, value);

        ui->txtKey->setText("");
        ui->txtValue->setText("");
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

    // borramos el contenido de este objeto
    jsondetalles = QJsonObject();

    QTreeWidgetItem *itemnivelcero = new QTreeWidgetItem(ui->treeDetalles);
    int nivel = jsondetalles_lista.count();
    itemnivelcero->setText(0, QString("Datos %1").arg(nivel));

    nivelactivo = itemnivelcero;
}

void NuevaResolucion::aceptarResolucion(){

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
    query.bindValue(":capitulo", capitulo_origen);
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

void NuevaResolucion::introducirJson(const int id){

    QSqlQuery query;

    /*
     * ponemos esto pq si hay un jsondetalles que no se ha metido
     * se perdería, pero hay que encontrar un sistema mejor
     */
    if (!jsondetalles.isEmpty())
        jsondetalles_lista.append(jsondetalles);

    for (int var = 0; var < jsondetalles_lista.size(); ++var) {

        /*
         * el asunto es el siguiente:
         * 1. construimos un QJsonDocument con ese QJsonobject de la lista, pq eso permite luego pasarlo
         *    a una cadena de texto con toJson()
         * 3. lo metemos en una puta variable, pq si no no funciona....
         */
        QJsonDocument jsondoc(jsondetalles_lista.at(var));
        QString jsonfinal = jsondoc.toJson(QJsonDocument::Compact);

        query.prepare("INSERT INTO resoluciones_detalles(resolucion_id, detalle) VALUES(:resolucionid, :json)");
        query.bindValue(":resolucionid", id);
        query.bindValue(":json", jsonfinal);
        query.exec();
    }
}

void NuevaResolucion::introducirTemas(const int id){
    for (int i = 0; i < temas_lista.size(); ++i) {

        QSqlQuery query;
        query.prepare("INSERT INTO temas_resoluciones(tema_id, resolucion_id) VALUES (:tema, :resolucion)");
        query.bindValue(":tema", temas_lista.at(i).id);
        query.bindValue(":resolucion", id);
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

    if (!key.isEmpty())
        m_values->setQuery(QString("SELECT DISTINCT value from resoluciones_detalles, json_each_text(detalle) "
                               "WHERE key='%1' ORDER BY value;").arg(key));

}

void NuevaResolucion::on_btNuevaPersona_clicked(){

    NuevaPersona *persona = new NuevaPersona(this);
    persona->show();
}

void NuevaResolucion::on_btNuevaCasa_clicked(){

    NuevaCasa *casa = new NuevaCasa(this);
    casa->show();
}

void NuevaResolucion::on_btNuevoLugar_clicked(){

    QString lugar;
    lugar = QInputDialog::getText(this, "Introduzca un nuevo lugar", "Lugar (nombre,país) ");

    if (!lugar.isEmpty()){
        m_lugares->AnadirLugar(lugar);
    }
}
