#include "dlginfraccionentrada.h"

#include <QCompleter>
#include <QKeyEvent>
#include <QListWidgetItem>
#include <QModelIndex>
#include <QSqlQueryModel>

#include "ui_dlginfraccionentrada.h"

const QString sql_tipo =
    "SELECT DISTINCT details->'declaracion_infraccion'->>'infraccion_tipo' AS "
    "tipo "
    "FROM resolutions_details WHERE details ? 'declaracion_infraccion' ORDER "
    "BY tipo;";

const QString sql_infraccion =
    "SELECT DISTINCT details->'declaracion_infraccion'->>'infraccion_asunto' "
    "AS asunto "
    "FROM resolutions_details WHERE details ? 'declaracion_infraccion' ORDER "
    "BY asunto;";

const QString sql_infractores =
    "SELECT DISTINCT "
    "jsonb_array_elements_text(details->'declaracion_infraccion'->'infraccion_"
    "infractores') AS infractores "
    "FROM resolutions_details WHERE "
    "details->'declaracion_infraccion'->'infraccion_infractores' IS NOT NULL "
    "ORDER BY infractores;";

dlgInfraccionEntrada::dlgInfraccionEntrada(QWidget *parent)
    : QWidget(parent), ui(new Ui::dlgInfraccionEntrada)
{
  ui->setupUi(this);

  ui->txtInfractor->installEventFilter(this);

  connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
  connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
  connect(ui->btEliminar, SIGNAL(clicked(bool)), this, SLOT(quitarInfractor()));

  cargarModelos();
}

dlgInfraccionEntrada::~dlgInfraccionEntrada() { delete ui; }

void dlgInfraccionEntrada::aceptar()
{
  infraccion.setTipo(ui->txtTipo->text());

  // qué pasa si la infracción está vacía?
  infraccion.setInfraccion(ui->txtInfraccion->text());
  infraccion.setInfractores(lista_infractores);

  ExtraInfos e = ui->wdExtras->getExtraInfos();
  infraccion.setExtras(e);

  if (ui->wdNotas->haCambiado()) infraccion.setNota(ui->wdNotas->getNotas());

  emit(aceptarInfraccion(infraccion));

  parentWidget()->close();
}

void dlgInfraccionEntrada::anadirInfractor()
{
  if (!ui->txtInfractor->text().isEmpty()) {
    lista_infractores.append(ui->txtInfractor->text());
    QListWidgetItem *item =
        new QListWidgetItem(ui->txtInfractor->text(), ui->lwInfractores);
    ui->txtInfractor->setText("");
  }
}

void dlgInfraccionEntrada::quitarInfractor()
{
  QModelIndex idx = ui->lwInfractores->currentIndex();

  if (!idx.isValid()) return;

  QString infractor = idx.data().toString();

  for (int i = 0; i < lista_infractores.size(); ++i) {
    if (lista_infractores.value(i) == infractor) {
      lista_infractores.removeAt(i);
      break;
    }
  }

  ui->lwInfractores->takeItem(ui->lwInfractores->currentRow());
}

void dlgInfraccionEntrada::cerrar() { parentWidget()->close(); }

bool dlgInfraccionEntrada::eventFilter(QObject *obj, QEvent *e)
{
  if (e->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
    if (keyEvent->key() == Qt::Key_Return) {
      anadirInfractor();
      return true;
    }
  }

  /*
   * atención aquí lo importante es poner QWidget!
   * si pongo dlgPenaEntrada no funciona!!
   */
  return QWidget::eventFilter(obj, e);
}

void dlgInfraccionEntrada::cargarModelos()
{
  infractores_model = new QSqlQueryModel(this);
  infractores_model->setQuery(sql_infractores);

  infractores_completer = new QCompleter(infractores_model, this);
  infractores_completer->setCompletionColumn(0);
  infractores_completer->setCaseSensitivity(Qt::CaseInsensitive);
  ui->txtInfractor->setCompleter(infractores_completer);

  tipos_model = new QSqlQueryModel(this);
  tipos_model->setQuery(sql_tipo);

  tipos_completer = new QCompleter(tipos_model, this);
  tipos_completer->setCompletionColumn(0);
  tipos_completer->setCaseSensitivity(Qt::CaseInsensitive);
  ui->txtTipo->setCompleter(tipos_completer);

  infraccion_model = new QSqlQueryModel(this);
  infraccion_model->setQuery(sql_infraccion);

  infraccion_completer = new QCompleter(infraccion_model, this);
  infraccion_completer->setCompletionColumn(0);
  infraccion_completer->setCaseSensitivity(Qt::CaseInsensitive);
  ui->txtInfraccion->setCompleter(infraccion_completer);
}
