#include "dlglicenciaentrada.h"

#include <QCompleter>
#include <QDebug>
#include <QListWidgetItem>
#include <QMdiSubWindow>
#include <QModelIndex>
#include <QSqlQueryModel>

#include "dlgseleccionargeneral.h"
#include "src/widgets/myqmdiarea.h"
#include "ui_dlglicenciaentrada.h"

const QString sql_otorgantes =
    "SELECT DISTINCT jsonb_array_elements_text(details->'otorgante') AS "
    "otorgante "
    "FROM resolutions_details WHERE details->>'otorgante' IS NOT NULL "
    "ORDER BY otorgante;";
const QString sql_tipo =
    "SELECT DISTINCT details->>'licencia_tipo' AS tipo "
    "FROM resolutions_details WHERE details ? 'licencia' ORDER BY tipo;";
const QString sql_asunto =
    "SELECT DISTINCT details->>'licencia_asunto' AS asunto "
    "FROM resolutions_details WHERE details ? 'licencia' ORDER BY asunto;";
const QString sql_receptores =
    "SELECT DISTINCT jsonb_array_elements_text(details->'receptor') AS "
    "receptor "
    "FROM resolutions_details WHERE details->>'receptor' IS NOT NULL "
    "ORDER BY receptor";

dlgLicenciaEntrada::dlgLicenciaEntrada(QWidget *parent)
    : QDialog(parent), ui(new Ui::dlgLicenciaEntrada)
{
  ui->setupUi(this);

  mdiarea = MyQmdiArea::Instance(this);

  connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
  connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
  connect(ui->btQuitarOtorgante, SIGNAL(clicked(bool)), this,
          SLOT(quitarOtorgante()));
  connect(ui->btQuitarReceptor, SIGNAL(clicked(bool)), this,
          SLOT(quitarReceptor()));
  connect(ui->txtOtorgante, SIGNAL(returnPressed()), this,
          SLOT(anadirOtorgante()));
  connect(ui->txtReceptor, SIGNAL(returnPressed()), this,
          SLOT(anadirReceptor()));
  connect(ui->txtProvincia, SIGNAL(dobleclick()), this,
          SLOT(anadirProvincia()));
  connect(ui->txtCasa, SIGNAL(dobleclick()), this, SLOT(anadirCasa()));

  cargarModelos();

  ui->txtOtorgante->installEventFilter(this);
  ui->txtReceptor->installEventFilter(this);
}

dlgLicenciaEntrada::~dlgLicenciaEntrada() { delete ui; }

void dlgLicenciaEntrada::aceptar()
{
  ExtraInfos extras = ui->wdExtras->getExtraInfos();

  licencia_activa.setLicenciaTipo(ui->txtTipo->text());
  licencia_activa.setOtorgantes(otorgantes);
  licencia_activa.setReceptores(receptores);
  licencia_activa.setAsunto(ui->txtAsunto->text());
  licencia_activa.setExtraInfos(extras);

  if (ui->wdNotas->haCambiado())
    licencia_activa.setNotas(ui->wdNotas->getNotas());

  if (provincia_seleccionada != 0)
    licencia_activa.setProvincia(provincia_seleccionada);

  if (casa_seleccionada != 0) licencia_activa.setCasa(casa_seleccionada);

  emit(aceptarLicencia(licencia_activa));

  close();
}

void dlgLicenciaEntrada::anadirReceptor()
{
  if (!ui->txtReceptor->text().isEmpty()) {
    receptores.append(ui->txtReceptor->text());
    QListWidgetItem *item =
        new QListWidgetItem(ui->txtReceptor->text(), ui->lwReceptores);
    ui->txtReceptor->setText("");
  }
}

void dlgLicenciaEntrada::quitarReceptor()
{
  QModelIndex idx = ui->lwReceptores->currentIndex();

  if (!idx.isValid()) return;

  QString receptor = idx.data().toString();

  for (int i = 0; i < receptores.size(); ++i) {
    if (receptores.value(i) == receptor) {
      receptores.removeAt(i);
      break;
    }
  }

  ui->lwReceptores->takeItem(ui->lwReceptores->currentRow());
}

void dlgLicenciaEntrada::anadirOtorgante()
{
  if (!ui->txtOtorgante->text().isEmpty()) {
    otorgantes.append(ui->txtOtorgante->text());
    QListWidgetItem *item =
        new QListWidgetItem(ui->txtOtorgante->text(), ui->lwOtorgantes);
    // por qué coño no funciona esto o funciona erráticamente???
    ui->txtOtorgante->setText("");
  }
}

void dlgLicenciaEntrada::quitarOtorgante()
{
  QModelIndex idx = ui->lwOtorgantes->currentIndex();

  if (!idx.isValid()) return;

  QString otorgante = idx.data().toString();

  for (int i = 0; i < otorgantes.size(); ++i) {
    if (otorgantes.value(i) == otorgante) {
      otorgantes.removeAt(i);
      break;
    }
  }

  ui->lwOtorgantes->takeItem(ui->lwOtorgantes->currentRow());
}

void dlgLicenciaEntrada::anadirProvincia()
{
  dlgSeleccionarGeneral *dlgSeleccionar =
      new dlgSeleccionarGeneral(PROVINCIA, true, this);
  connect(dlgSeleccionar, SIGNAL(provinciaEscogidaSignal(Provincia)), this,
          SLOT(recibirProvincia(Provincia)));

  QMdiSubWindow *window = mdiarea->addSubWindow(dlgSeleccionar);
  window->show();
}

void dlgLicenciaEntrada::anadirCasa()
{
  dlgSeleccionarGeneral *dlgSeleccionar =
      new dlgSeleccionarGeneral(CASA, true, this);
  connect(dlgSeleccionar, SIGNAL(casaEscogidaSignal(Casa)), this,
          SLOT(recibirCasa(Casa)));

  QMdiSubWindow *window = mdiarea->addSubWindow(dlgSeleccionar);
  window->show();
}

void dlgLicenciaEntrada::recibirCasa(Casa casa)
{
  casa_seleccionada = casa.getId();
  QString valor = casa.getNombre();

  ui->txtCasa->setText(valor);
}

void dlgLicenciaEntrada::recibirProvincia(Provincia provincia)
{
  provincia_seleccionada = provincia.getId();
  QString valor = provincia.getNombre();

  ui->txtProvincia->setText(valor);
}

void dlgLicenciaEntrada::cerrar() { parentWidget()->close(); }

bool dlgLicenciaEntrada::eventFilter(QObject *obj, QEvent *e)
{
  if (obj == ui->txtOtorgante) {
    if (e->type() == QEvent::KeyPress) {
      QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
      if (keyEvent->key() == Qt::Key_Return) {
        anadirOtorgante();
        return true;
      }
    }
  }
  else if (obj == ui->txtReceptor) {
    if (e->type() == QEvent::KeyPress) {
      QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
      if (keyEvent->key() == Qt::Key_Return) {
        anadirReceptor();
        return true;
      }
    }
  }

  /*
   * atención aquí lo importante es poner QDialog!
   * si pongo dlgPenaEntrada no funciona!!
   */
  return QDialog::eventFilter(obj, e);
}

void dlgLicenciaEntrada::cargarModelos()
{
  otorgantes_model = new QSqlQueryModel(this);
  otorgantes_model->setQuery(sql_otorgantes);

  otorgantes_completer = new QCompleter(otorgantes_model, this);
  otorgantes_completer->setCompletionColumn(0);
  otorgantes_completer->setCaseSensitivity(Qt::CaseInsensitive);
  ui->txtOtorgante->setCompleter(otorgantes_completer);

  tipos_model = new QSqlQueryModel(this);
  tipos_model->setQuery(sql_tipo);

  tipos_completer = new QCompleter(tipos_model, this);
  tipos_completer->setCompletionColumn(0);
  tipos_completer->setCaseSensitivity(Qt::CaseInsensitive);
  ui->txtTipo->setCompleter(tipos_completer);

  receptores_model = new QSqlQueryModel(this);
  receptores_model->setQuery(sql_receptores);

  receptores_completer = new QCompleter(receptores_model, this);
  receptores_completer->setCompletionColumn(0);
  receptores_completer->setCaseSensitivity(Qt::CaseInsensitive);
  ui->txtReceptor->setCompleter(receptores_completer);

  asuntos_model = new QSqlQueryModel(this);
  asuntos_model->setQuery(sql_asunto);

  asuntos_completer = new QCompleter(asuntos_model, this);
  asuntos_completer->setCompletionColumn(0);
  asuntos_completer->setCaseSensitivity(Qt::CaseInsensitive);
  ui->txtAsunto->setCompleter(asuntos_completer);
}
