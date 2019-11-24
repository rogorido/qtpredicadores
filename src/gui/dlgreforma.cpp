#include "dlgreforma.h"

#include <QCompleter>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include "dlgseleccionargeneral.h"
#include "ui_dlgreforma.h"

dlgReforma::dlgReforma(QWidget *parent)
    : QDialog(parent), ui(new Ui::dlgReforma)
{
  ui->setupUi(this);

  connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(close()));
  connect(ui->txtLugar, SIGNAL(dobleclick()), this, SLOT(anadirLugar()));
  connect(ui->btOk, SIGNAL(clicked()), this, SLOT(aceptar()));

  cargarModelos();
}

dlgReforma::~dlgReforma() { delete ui; }

void dlgReforma::anadirLugar()
{
  dlgSeleccionarGeneral *dlgSeleccionar =
      new dlgSeleccionarGeneral(LUGAR, true, this);
  dlgSeleccionar->show();

  connect(dlgSeleccionar, SIGNAL(lugarEscogidoSignal(Lugar)), this,
          SLOT(recibirLugar(Lugar)));
}

void dlgReforma::quitarLugar()
{
  lugar_struct = elementopareado();
  ui->txtLugar->clear();
}

void dlgReforma::aceptar()
{
  QSqlQuery query;
  QString orden;
  bool male;
  QString otrosdatos;

  if (ui->txtOrden->text().isEmpty()) {
    int ret = QMessageBox::warning(this, "No hay tipo de orden ",
                                   "Introduzca algún tipo de orden religiosa");
    Q_UNUSED(ret)
    return;
  }

  if (lugar_struct.id == 0) {
    int ret = QMessageBox::warning(this, "No hay ningún lugar.",
                                   "Introduzca algún lugar.");
    Q_UNUSED(ret)
    return;
  }

  orden = ui->txtOrden->text();
  male = ui->ckMasculino->checkState();
  otrosdatos = crearJsonDatos();

  query.prepare(
      "INSERT INTO reform.reform_houses(place_id, religious_order, male, "
      "other_data) "
      "VALUES(:lugar, :orden, :masculino, :otrosdatos)");
  query.bindValue(":lugar", lugar_struct.id);
  query.bindValue(":orden", orden);
  query.bindValue(":masculino", male);
  if (!otrosdatos.isEmpty())
    query.bindValue(":otrosdatos", otrosdatos);
  else
    query.bindValue(":otrosdatos", QVariant(QVariant::String));

  if (!query.exec()) {
    qDebug() << query.lastError();
    qDebug() << "esta es la query: " << query.executedQuery().toUtf8();

    int ret = QMessageBox::warning(this, "Error al introducir los datos.",
                                   "Error al introducir los datos.");
    Q_UNUSED(ret)
  }
  else {
    borrarCampos();
    ui->txtLugar->setFocus();
  }
}

void dlgReforma::recibirLugar(Lugar lugar)
{
  lugar_struct.id = lugar.getId();
  lugar_struct.elemento = lugar.getLugar();

  ui->txtLugar->setText(lugar_struct.elemento);
}

void dlgReforma::cargarModelos()
{
  m_ordenes = new QSqlQueryModel(this);
  m_ordenes_completer = new QCompleter(this);

  m_ordenes->setQuery(
      "SELECT DISTINCT religious_order FROM reform.reform_houses ORDER BY "
      "religious_order");
  m_ordenes_completer->setModel(m_ordenes);
  m_ordenes_completer->setCompletionColumn(0);
  m_ordenes_completer->setCaseSensitivity(Qt::CaseInsensitive);
  ui->txtOrden->setCompleter(m_ordenes_completer);
}

QString dlgReforma::crearJsonDatos()
{
  QJsonObject json;
  QJsonDocument json_document;
  QString final = "";

  if (ui->ckAbandonado->checkState())
    json.insert("abandoned", QJsonValue(true));

  if (!ui->txtAbandonadoAno->text().isEmpty())
    json.insert("abandoned_year", QJsonValue(ui->txtAbandonadoAno->text()));

  if (ui->ckRetomado->checkState()) json.insert("reopened", QJsonValue(true));

  if (!ui->txtRetomadoAno->text().isEmpty())
    json.insert("reopened_year", QJsonValue(ui->txtRetomadoAno->text()));

  if (json.empty())
    return final;
  else {
    json_document.setObject(json);
    final = json_document.toJson(QJsonDocument::Compact);
    return final;
  }
}

void dlgReforma::borrarCampos()
{
  lugar_struct = elementopareado();
  ui->txtLugar->clear();
  ui->txtOrden->clear();
  ui->txtAbandonadoAno->clear();
  ui->txtRetomadoAno->clear();
  ui->ckMasculino->setCheckState(Qt::Unchecked);
  ui->ckAbandonado->setCheckState(Qt::Unchecked);
  ui->ckRetomado->setCheckState(Qt::Unchecked);
}
