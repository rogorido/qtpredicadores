#include "dlgresoluciones.h"
#include "ui_dlgresoluciones.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMdiSubWindow>
#include <QMessageBox>

#include "models/qjsonmodel.h"

#include "widgets/myqmdiarea.h"

#include "gui/dlgseleccionargeneral.h"
#include "gui/dlgdetalles.h"

const QString sql_general="SELECT DISTINCT ON (r.resolution_id) * FROM resolutions r "
                          "LEFT JOIN resolutions_details rd ON r.resolution_id = rd.resolution_id "
                          "LEFT JOIN chapters c ON r.chapter = c.chapter_id";

DlgResoluciones::DlgResoluciones(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DlgResoluciones)
{
    ui->setupUi(this);

    mdiarea = MyQmdiArea::Instance(this);

    json_model = new QJsonModel(this);
    ui->twDetalles->setModel(json_model);

    json_anadir_model = new QJsonModel(this);

    cargarModelos();
    cargarMapper();
    cargarInfos();

    connect(ui->twResoluciones->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(seleccionarResolucion(QModelIndex)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(aplicarFiltro()));

}

DlgResoluciones::~DlgResoluciones()
{
    delete ui;
}

void DlgResoluciones::seleccionarResolucion(const QModelIndex &idx)
{

    /* entiendo q con esto consigo que los campos de abajo
     * se actualicen... por que si no, ¿para qué puse esto?
     */
    mapper_data->setCurrentModelIndex(idx);

    /*
     * sacamos el índice de la columna 0 que es donde está
     * la id de la resolución, para luego convertirla en int
     * y usarla en el filtro del otro modelo.
     */
    QModelIndex indice = idx.model()->index(idx.row(), 0);
    if (!indice.isValid())
        return;

    resolucion_id = resoluciones_model->data(indice, Qt::DisplayRole).toInt();
    temas_model->setFilter(QString("resolution_id=%1").arg(resolucion_id));

    cargarDetalles(resolucion_id);
}

void DlgResoluciones::recibirNuevoTema(Tema t)
{
    int tema_id = t.getId();

    QSqlQuery query;
    query.prepare("INSERT INTO resolutions_themes(theme_id, resolution_id) VALUES(:tema, :resolucion)");
    query.bindValue(":tema", tema_id);
    query.bindValue(":resolucion", resolucion_id);
    query.exec();

    temas_model->select();
    temas_model->setFilter(QString("resolution_id=%1").arg(resolucion_id));
}

void DlgResoluciones::recibirNuevoJsonDetalles()
{

    QSqlQuery query;
    int totaljson = json_anadir_model->getSize();

    if (totaljson == 0)
        return;

    qDebug() << "la resulu-id es: " << resolucion_id;

    for (int var = 0; var < totaljson; ++var) {

        QString jsonfinal = json_anadir_model->getJsonString(var);

        query.prepare("INSERT INTO resolutions_details(resolution_id, details) VALUES(:resolucionid, :json)");
        query.bindValue(":resolucionid", resolucion_id);
        query.bindValue(":json", jsonfinal);
        query.exec();

        /*
         * y ahora actualizamos el modelo de la view
         */
        QJsonObject json_temporal = json_anadir_model->getJsonObject(var);
        json_model->anadirJson(json_temporal);
    }

    json_model->resetearModelo();

    // borramos el contenido json_anadir_model...
    json_anadir_model->clear();

    /*
     * NOTE: esto es un poco cutre, pero volver a cargar los detalles
     * pq así se vuelve a llenar la lista de ids_details pq si no,
     * puede estar vacía... Realmente habría que hacer aquí algún sistema
     * para coger lo que se haya metido pero da igual...
     */
    cargarDetalles(resolucion_id);
}

void DlgResoluciones::cargarDetalles(int id)
{
    QSqlQuery query;
    QString sql;
    QJsonDocument json;

    sql = QString("SELECT detail_id, details FROM resolutions_details WHERE resolution_id=%1").arg(id);
    query.exec(sql);

    // borramos lo que ya está
    json_model->clear();
    ids_resolutions_details.clear();

    /*
     * joder, que lío hay que hacer para construir un json...
     * hay que usar eso de QByteArray pq con una QString normal
     * no hay manera...
     */
    while (query.next()) {
        int id = query.value(0).toInt();
        QByteArray datos = query.value(1).toByteArray();
        json = QJsonDocument::fromJson(datos);
        /*
         * tenemos que pasar json.object que construye un
         * QjsonObject, que es al parecer tb un QJsonValue
         * y es lo que pide anadirJson...
         */
        json_model->anadirJson(json.object());

        ids_resolutions_details << id;
    }

    json_model->resetearModelo();

    json_model->setIdDetails(ids_resolutions_details);

}

void DlgResoluciones::aplicarFiltro()
{
    resoluciones_model->setQuery(sql_general + QString(" WHERE details ?| array['mandato', 'prohibición',"
                                                       " 'comisión', 'admonición'];"));

}

void DlgResoluciones::on_btAnadirTema_clicked()
{
    dlgseleccionar = new dlgSeleccionarGeneral(TEMA, this);
    connect(dlgseleccionar, SIGNAL(temaEscogidoSignal(Tema)), this, SLOT(recibirNuevoTema(Tema)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgseleccionar);
    window->show();
}

void DlgResoluciones::on_btQuitarTema_clicked()
{
    /*
     * sigo sin entender cómo coño es tan difícil esto de
     * extraer el valor de una tabla, del modelo subyacente, etc.
     */
    int row = ui->twTemas->currentIndex().row();
    QModelIndex idx = temas_model->index(row, 0); // columna 0, pq está el id

    if (!idx.isValid())
        return;

    int valor = temas_model->data(idx, Qt::DisplayRole).toInt();

    QSqlQuery query;
    query.prepare("DELETE FROM resolutions_themes WHERE resolutions_themes_id=:valor");
    query.bindValue(":valor", valor);
    query.exec();

    temas_model->select();
    temas_model->setFilter(QString("resolution_id=%1").arg(resolucion_id));
}

void DlgResoluciones::on_btAnadirDetalles_clicked()
{
    dlgDetalles *dlgdetalles = new dlgDetalles(json_anadir_model, RESOLUCION, true, this);
    connect(dlgdetalles, SIGNAL(accepted()), this, SLOT(recibirNuevoJsonDetalles()));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgdetalles);
    window->show();
}

void DlgResoluciones::on_btBorrarDetalles_clicked()
{
    /*
     * la idea es la siguiente: cogemos el índice; si no es válido
     * salimos sin más. Si es válido continúa y coge el del padre.
     * Y aquí está el truco: si el índice del padre no es válido, eso
     * quiere decir que estamos ya en el nivel superior y por tanto
     * el índice que nos interesa es idx, pero si es válido, lo que
     * nos interesa es el índice padre.
     *
     * NOTE: esto evidentemente sólo sirve cuando hay solo un subnivel,
     * si hubiera más subniveles no funcionaría!
     */
    QSqlQuery query;
    QModelIndex idx = ui->twDetalles->currentIndex();
    int ordinal;

    if (!idx.isValid())
        return;

    QModelIndex padre = idx.parent();

    if (!padre.isValid())
        ordinal = idx.row();
    else
        ordinal = padre.row();

    /*
     * ahora necesitamos sacar el detail_id de la
     * lista para hacer una query DELETE.
     * tenemos que usar takeAt para eleminar ese elemetno de
     * la lista ids_resolutions_details
     */
    qDebug() << "tamaño de la lista de ids: " << ids_resolutions_details.size();
    int id_detail = ids_resolutions_details.takeAt(ordinal);
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Borrar detalles de resolución", "¿Seguro que quieres borrar este bloque de datos?",
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        query.exec(QString("DELETE FROM resolutions_details WHERE detail_id=%1").arg(id_detail));
        json_model->borrarJson(ordinal);
    }

}

void DlgResoluciones::cargarModelos()
{
    resoluciones_model = new QSqlQueryModel(this);
    resoluciones_model->setQuery(sql_general);
    resoluciones_model->setHeaderData(1, Qt::Horizontal, "Texto resolución");
    resoluciones_model->setHeaderData(2, Qt::Horizontal, "Capítulo");
    resoluciones_model->setHeaderData(3, Qt::Horizontal, "Epígrafe");
    ui->twResoluciones->setModel(resoluciones_model);
    ui->twResoluciones->hideColumn(0);
    ui->twResoluciones->setAlternatingRowColors(true);
    ui->twResoluciones->setColumnWidth(1, 80);
    //ui->twResoluciones->resizeColumnsToContents();
    //ui->twResoluciones->resizeRowsToContents();
    ui->twResoluciones->horizontalHeader()->setStretchLastSection(true);
    ui->twResoluciones->setSortingEnabled(true);
    ui->twResoluciones->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twResoluciones->setSelectionMode(QAbstractItemView::SingleSelection);

    // escogemos la primera línea del modelo...
    QModelIndex index = resoluciones_model->index(0,0);
    if (index.isValid()) {
        ui->twResoluciones->setCurrentIndex(index);
    }

    temas_model = new QSqlRelationalTableModel(this);
    temas_model->setTable("chapters.resolutions_themes");
    temas_model->setRelation(1, QSqlRelation("general.themes", "theme_id", "theme"));
    temas_model->setHeaderData(1, Qt::Horizontal, "Tema");
    temas_model->select();
    ui->twTemas->setModel(temas_model);
    ui->twTemas->hideColumn(0);
    ui->twTemas->hideColumn(2);
    ui->twTemas->horizontalHeader()->setStretchLastSection(true);
    ui->twTemas->setAlternatingRowColors(true);
    ui->twTemas->resizeColumnsToContents();
    ui->twTemas->resizeRowsToContents();
    ui->twTemas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twTemas->setSelectionMode(QAbstractItemView::SingleSelection);

}

void DlgResoluciones::cargarMapper()
{
    mapper_data = new QDataWidgetMapper(this);
    mapper_data->setModel(resoluciones_model);
    mapper_data->addMapping(ui->txtResolucion, 1);
    mapper_data->addMapping(ui->txtResolucionResumen,3);

}

void DlgResoluciones::cargarInfos()
{
    ui->lblTotalResoluciones->setText(QString("Resoluciones: %1").arg(resoluciones_model->rowCount()));
}
