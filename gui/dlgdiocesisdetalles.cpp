#include "dlgdiocesisdetalles.h"
#include "ui_dlgdiocesisdetalles.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QCompleter>
#include <QMdiSubWindow>
#include <QSqlError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QDebug>

#include "gui/dlgseleccionargeneral.h"
#include "widgets/myqmdiarea.h"
#include "objs/variados.h"

const QString sql_lord = "SELECT DISTINCT details->>'temporal_lord' AS lord FROM general.dioceses_details ORDER BY lord";
const QString sql_keys = "SELECT DISTINCT jsonb_object_keys(details) AS keys FROM general.dioceses_details ORDER BY keys";
const QString sql_values = "SELECT DISTINCT value FROM dioceses_details, jsonb_each_text(details) "
                                "WHERE value !~ '[0-9]'";
const QString sql_divisas = "SELECT DISTINCT details->>'mensa_currency' as currency FROM general.dioceses_details "
                            "UNION SELECT DISTINCT details->>'tax_currency' as currency FROM general.dioceses_details "
                            "ORDER BY currency";


dlgDiocesisDetalles::dlgDiocesisDetalles(int diocesis_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgDiocesisDetalles),
    dioc_id(diocesis_id)
{
    ui->setupUi(this);

    mdiarea = MyQmdiArea::Instance(this);

    connect(ui->txtSufraganea, SIGNAL(dobleclick()), this, SLOT(AnadirArchiDiocesis()));
    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(cancelar()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptar()));

    cargarModelos();
    ui->spTomo->setFocus();

}

dlgDiocesisDetalles::~dlgDiocesisDetalles()
{
    delete ui;
}

void dlgDiocesisDetalles::aceptar()
{
    QJsonObject json;
    QJsonDocument json_doc;
    ExtraInfos extras;

    int tomo = ui->spTomo->value();
    int anoref = ui->spAnoRef->value();
    int numero_obispos = ui->spNumeroObispos->value();
    int rentas = ui->spRenta->value();
    int tasa = ui->spTaxa->value();
    QString rentas_divisa = ui->txtRentasDivisa->text();
    QString tasas_divisa = ui->txtTasaDivisa->text();
    QString senor = ui->txtSenorTemporal->text();
    int canonigos = ui->spCanonicos->value();
    int dignidades = ui->spDignidades->value();
    int beneficiados = ui->spBeneficiados->value();
    bool inmediata = ui->ckInmediata->checkState();
    bool sindatos = ui->ckSinDatos->checkState();

    extras = ui->wdExtras->getExtraInfos();

    if (sindatos){
        json.insert("without_data", QJsonValue(sindatos));
        json_doc = QJsonDocument(json);
        introducirDatos(json_doc);
        return;
    }

    json.insert("volume", QJsonValue(tomo));
    if (anoref != 0) json.insert("year", QJsonValue(anoref));
    if (rentas != 0) json.insert("mensa_episcopalis", QJsonValue(rentas));
    if (tasa != 0) json.insert("taxa", QJsonValue(tasa));
    if (!rentas_divisa.isEmpty()) json.insert("mensa_currency", QJsonValue(rentas_divisa));
    if (!tasas_divisa.isEmpty()) json.insert("tax_currency", QJsonValue(tasas_divisa));
    if (numero_obispos != 0) json.insert("number_bishops", QJsonValue(numero_obispos));
    if (!senor.isEmpty()) json.insert("temporal_lord", QJsonValue(senor));
    if (canonigos != 0) json.insert("canonicates", QJsonValue(canonigos));
    if (dignidades != 0) json.insert("dignities", QJsonValue(dignidades));
    if (beneficiados != 0) json.insert("beneficiates", QJsonValue(beneficiados));
    if (sufraganea_id != 0) json.insert("sufraganea", QJsonValue(sufraganea_id));
    json.insert("saint_siege", QJsonValue(inmediata));
    json.insert("without_data", QJsonValue(sindatos));

    if (extras.size() > 0) {
        for (int i = 0; i < extras.size(); ++i) {
            QPair<QString, QString> par;
            par = extras.at(i);
            json.insert(par.first, QJsonValue(par.second));
        }
    }

    /*
     * TODO: falta lo de las notas!
     */
    json_doc = QJsonDocument(json);
    introducirDatos(json_doc);

}

void dlgDiocesisDetalles::cancelar()
{
    parentWidget()->close();

}

void dlgDiocesisDetalles::AnadirArchiDiocesis()
{
    dlgSeleccionarGeneral *seleccion = new dlgSeleccionarGeneral(DIOCESIS, this);
    connect(seleccion, SIGNAL(diocesisEscogidaSignal(Diocesis)), this, SLOT(recibirArchiDiocesis(Diocesis)));

    QMdiSubWindow *window = mdiarea->addSubWindow(seleccion);
    window->show();
}

void dlgDiocesisDetalles::recibirArchiDiocesis(Diocesis diocesis)
{
    sufraganea_id = diocesis.getId();
    ui->txtSufraganea->setText(diocesis.getNombre());
}

void dlgDiocesisDetalles::cargarModelos()
{
    /*
     * FIXME: cuidado, ¿realmente qué pasa si la query está
     * vacía? se inicializa el model? Hace crash?
     */
    m_senores = new QSqlQueryModel(this);
    senores_completer = new QCompleter(this);

    m_senores->setQuery(sql_lord);
    senores_completer->setModel(m_senores);
    senores_completer->setCompletionColumn(0);
    senores_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtSenorTemporal->setCompleter(senores_completer);

    m_divisas = new QSqlQueryModel(this);
    divisas_completer = new QCompleter(this);

    m_divisas->setQuery(sql_divisas);
    divisas_completer->setModel(m_divisas);
    divisas_completer->setCompletionColumn(0);
    divisas_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtRentasDivisa->setCompleter(divisas_completer);
    ui->txtTasaDivisa->setCompleter(divisas_completer);

    ui->wdExtras->recibirConsultasCompleter(sql_keys, sql_values);

}

void dlgDiocesisDetalles::borrarCampos()
{
    // dejamos el tomo, año como están porque seguramente meto varios

    ui->ckInmediata->setCheckState(Qt::Unchecked);
    ui->ckSinDatos->setCheckState(Qt::Unchecked);
    ui->spRenta->setValue(0);
    ui->spTaxa->setValue(0);
    ui->spNumeroObispos->setValue(0);
    ui->spCanonicos->setValue(0);
    ui->spDignidades->setValue(0);
    ui->spBeneficiados->setValue(0);
    ui->txtSenorTemporal->setText("");
    ui->txtRentasDivisa->setText("");
    ui->txtTasaDivisa->setText("");
    ui->txtSufraganea->setText("");

    ui->wdExtras->clear();
    ui->wdNotas->reiniciar();

    sufraganea_id = 0;

    ui->spTomo->setFocus();

}

void dlgDiocesisDetalles::introducirDatos(QJsonDocument json_doc)
{
    QSqlQuery query;
    QString json_str = json_doc.toJson(QJsonDocument::Compact);

    query.prepare("INSERT INTO general.dioceses_details(diocese_id, details) "
                  "VALUES(:diocese_id, :json)");
    query.bindValue(":diocese_id", dioc_id);
    query.bindValue(":json", json_str);

    if (!query.exec()){
        qDebug() << query.lastError();
        qDebug() << "esta es la query: " << query.executedQuery().toUtf8();
    }
    else {
        qDebug() << "éxito con la query";
        cancelar();
        //borrarCampos();
    }

}
