#include "dlgnuevaresolucion.h"
#include "ui_dlgnuevaresolucion.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QTableWidget>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QCompleter>
#include <QJsonValue>
#include <QSqlError>
#include <QStringListModel>

#include <QDebug>

#include "models/temasmodel.h"
#include "models/resolucionesmodel.h"
#include "models/qjsonmodel.h"
#include "dlgdetalles.h"
#include "objs/resolucion.h"
#include "gui/dlgtemas.h"
#include "gui/dlgseleccionargeneral.h"

dlgNuevaResolucion::dlgNuevaResolucion(int capitulo,
                                 QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgNuevaResolucion), capitulo_origen(capitulo)
{
    ui->setupUi(this);

    jsongestor = new QJsonModel(this);
    m_resoluciones = ResolucionesModel::InstanceModel();

    dlgdetalles = new dlgDetalles(jsongestor, RESOLUCION, false, this);
    // pasamos una referencia: ver notas en el header
    dlgtemas = new dlgTemas(&temas_lista, this);

    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarResolucion()));
    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(cerrar()));
    connect(ui->txtProvincia, SIGNAL(dobleclick()), this, SLOT(anadirProvincia()));
    connect(ui->btQuitarProvincia, SIGNAL(clicked()), this, SLOT(quitarProvincia()));
    connect(ui->txtCapitulo, SIGNAL(dobleclick()), this, SLOT(anadirCapitulo()));
    connect(ui->btQuitarCapitulo, SIGNAL(clicked()), this, SLOT(quitarCapitulo()));

    cargarModelos();

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

    Resolucion *resolucion = new Resolucion();
    QString resolucion_texto;

    resolucion_texto = ui->txtResolucion->toPlainText();

    if (resolucion_texto.isEmpty()){
        int ret = QMessageBox::warning(this, "No hay texto en la resolución general",
                                       "Introduzca por favor texto en la resolución");
        return;
    }

    if (capitulo_id == 0){
        int ret = QMessageBox::warning(this, "El capítulo esta vacío",
                                       "El capítulo esta vacío. Introduzca por favor el capítulo de la resolución");
        return;
    }

    /*
     * necesitamos quitar \\n y demás del texto
     */
    resolucion_texto = resolucion_texto.replace("-\n", "");
    resolucion_texto = resolucion_texto.simplified();

    QString resolucion_resumen = ui->txtResolucionResumen->toPlainText();
    QString resolucion_trad = ui->txtResolucionTraduccion->toPlainText();
    QString epigrafe = ui->txtEpigrafe->text();
    QString notas = ui->txtResolucionNotas->toPlainText();
    int interesante = ui->spInteresante->value();
    bool entendida = ui->chEntendida->checkState();
    bool volveramirar = ui->chVolverMirar->checkState();
    bool traducida = ui->chTradudida->checkState();
    bool razonada = ui->chRazonada->checkState();
    QString paginas = ui->txtPaginas->text();

    QStringList verbos = m_verbos->stringList();
    QStringList expresiones = m_expresiones->stringList();

    resolucion->setTexto(resolucion_texto);
    resolucion->setTextoResumido(resolucion_resumen);
    resolucion->setTextoTraducido(resolucion_trad);
    resolucion->setEpigrafe(epigrafe);
    resolucion->setInteres(interesante);
    resolucion->setEntendido(entendida);
    resolucion->setVolverMirar(volveramirar);
    resolucion->setTraducido(traducida);
    resolucion->setRazonada(razonada);
    resolucion->setCapitulo(capitulo_id);
    resolucion->setProvincia(provincia_id);
    resolucion->setVerbos(verbos);
    resolucion->setExpresiones(expresiones);
    resolucion->setPages(paginas);
    resolucion->setNotas(notas);

    if (m_resoluciones->anadirResolucion(resolucion)) {

      //QSqlQuery lastid("select currval('capitulos_capitulo_id_seq')");
      QSqlQuery lastid("select max(resolution_id) from resolutions");
      lastid.first();
      int id = lastid.value(0).toInt();
      introducirJson(id);
      introducirTemas(id);

      borrarCampos();

      return;
    }
    else {
        int ret = QMessageBox::warning(this, "Error al introducir la resolución",
                                       "Error al introducir la resolución en la BD");
        return;
    }

}

void dlgNuevaResolucion::introducirJson(const int id){

    QSqlQuery query;
    int totaljson;

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
        query.prepare("INSERT INTO resolutions_themes(theme_id, resolution_id) VALUES (:tema, :resolucion)");
        query.bindValue(":tema", temas_lista.at(i).id);
        query.bindValue(":resolucion", id);
        query.exec();
    }

}

void dlgNuevaResolucion::on_btDetalles_clicked()
{
    emit(abrirDetalles(dlgdetalles));
}

void dlgNuevaResolucion::on_btTemas_clicked(){

    dlgtemas->show();

    //connect(dlgtemas, SIGNAL(temasSeleccionadosSignal(QList<elementopareado>)), this, SLOT(recibirTemas(QList<elementopareado>)));
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

void dlgNuevaResolucion::recibirCapitulo(Capitulo capitulo){

    capitulo_id = capitulo.getId();

    QString capitulo_string = capitulo.getNombre() + QString(" (") + capitulo.getFechaInicio().toString() + QString(" )");

    ui->txtCapitulo->setText(capitulo_string);
}

void dlgNuevaResolucion::cerrar()
{
    parentWidget()->close();
}

void dlgNuevaResolucion::anadirCapitulo(){

    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(CAPITULO, this);

    dlgseleccionar->show();
    connect(dlgseleccionar, SIGNAL(capituloEscogidoSignal(Capitulo)), this, SLOT(recibirCapitulo(Capitulo)));

}

void dlgNuevaResolucion::quitarCapitulo(){

    capitulo_id = 0;
    ui->txtCapitulo->setText("");
}

void dlgNuevaResolucion::borrarCampos(){

    ui->txtEpigrafe->setText("");
    ui->txtProvincia->setText("");
    //ui->txtCapitulo->setText(""); ver abajo
    ui->txtResolucion->clear();
    ui->txtResolucionNotas->clear();
    ui->txtResolucionResumen->clear();
    ui->txtResolucionTraduccion->clear();
    ui->txtVerbo->setText("");
    ui->txtExpresion->setText("");

    ui->chEntendida->setCheckState(Qt::Unchecked);
    ui->chTradudida->setCheckState(Qt::Unchecked);
    ui->chVolverMirar->setCheckState(Qt::Unchecked);

    ui->spInteresante->setValue(0);

    jsongestor = new QJsonModel(this);
    dlgdetalles = new dlgDetalles(jsongestor, RESOLUCION, false, this);

    m_verbos = new QStringListModel();
    m_expresiones = new QStringListModel();
    ui->twVerbs->setModel(m_verbos);
    ui->twExpresiones->setModel(m_expresiones);

    temas_lista.clear();
    // pasamos una referencia: ver notas en el header
    dlgtemas = new dlgTemas(&temas_lista, this);

    provincia_id = 0;

    /*
     * dejamos el capítulo pq así puedo ir metiendo varias
     * resoluciones del mismo capítulo.
     */
    //capitulo_id = 0;

    ui->txtEpigrafe->setFocus();

}

void dlgNuevaResolucion::cargarModelos(){

    m_epigrafe = new QSqlQueryModel(this);
    m_epigrafe->setQuery("SELECT DISTINCT small_title FROM resolutions ORDER BY small_title;");

    m_epigrafe_completer = new QCompleter(m_epigrafe, this);
    m_epigrafe_completer->setCompletionColumn(0);
    m_epigrafe_completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->txtEpigrafe->setCompleter(m_epigrafe_completer);

    m_verbos = new QStringListModel();
    m_expresiones = new QStringListModel();

    ui->twVerbs->setModel(m_verbos);
    ui->twExpresiones->setModel(m_expresiones);

    m_verbos_usados = new QSqlQueryModel(this);
    m_verbos_usados->setQuery("SELECT DISTINCT unnest(verbs) AS verbos FROM resolutions ORDER BY verbos;");
    m_verbos_completer = new QCompleter(m_verbos_usados, this);
    m_verbos_completer->setCompletionColumn(0);
    m_verbos_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtVerbo->setCompleter(m_verbos_completer);

    m_expresiones_usados = new QSqlQueryModel(this);
    m_expresiones_usados->setQuery("SELECT DISTINCT unnest(expressions) AS expresiones FROM resolutions ORDER BY expresiones;");
    m_expresiones_completer = new QCompleter(m_expresiones_usados, this);
    m_expresiones_completer->setCompletionColumn(0);
    m_expresiones_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtExpresion->setCompleter(m_expresiones_completer);

}

void dlgNuevaResolucion::on_btAnadirVerbo_clicked(){

    QString verbo = ui->txtVerbo->text();

    if (verbo.isEmpty()){
        return;
    }

    // Get the position
    int row = m_verbos->rowCount();
    // Enable add one or more rows
    m_verbos->insertRows(row,1);
    // Get the row for Edit mode
    QModelIndex index = m_verbos->index(row);

    m_verbos->setData(index, verbo);

    ui->txtVerbo->setText("");

}

void dlgNuevaResolucion::on_btQuitarVerbo_clicked(){

    m_verbos->removeRows(ui->twVerbs->currentIndex().row(),1);
}

void dlgNuevaResolucion::on_btAnadirExpresion_clicked(){
    QString expresion = ui->txtExpresion->text();

    if (expresion.isEmpty()){
        return;
    }

    // Get the position
    int row = m_expresiones->rowCount();
    // Enable add one or more rows
    m_expresiones->insertRows(row,1);
    // Get the row for Edit mode
    QModelIndex index = m_expresiones->index(row);

    m_expresiones->setData(index, expresion);

    ui->txtExpresion->setText("");
}

void dlgNuevaResolucion::on_btQuitarExpresion_clicked(){

    m_expresiones->removeRows(ui->twExpresiones->currentIndex().row(), 1);
}
