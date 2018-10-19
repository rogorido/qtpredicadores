#include "dlgviajeentrada.h"
#include "ui_dlgviajeentrada.h"

#include <QKeyEvent>
#include <QMdiSubWindow>
#include <QListWidgetItem>
#include <QModelIndex>
#include <QSqlQueryModel>
#include <QCompleter>

#include "src/widgets/myqmdiarea.h"
#include "dlgseleccionargeneral.h"

const QString sql_motivos="SELECT DISTINCT jsonb_array_elements_text(details->'viaje'->'motivos') AS motivos "
                             "FROM persons_details WHERE details->'viaje'->>'motivos' IS NOT NULL "
                             "ORDER BY motivos";
const QString sql_motivos_muerte="SELECT DISTINCT details->'viaje'->>'motivo_muerte' AS motivo "
                             "FROM persons_details WHERE details->'viaje'->>'motivo_muerte' IS NOT NULL "
                             "ORDER BY motivo";
const QString sql_lugares_muerte="SELECT DISTINCT details->'viaje'->>'lugar_muerte' AS lugar "
                             "FROM persons_details WHERE details->'viaje'->>'lugar_muerte' IS NOT NULL "
                             "ORDER BY lugar";

const QDate fechainicial = QDate(1500, 1, 1);

dlgViajeEntrada::dlgViajeEntrada(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgViajeEntrada)
{
    ui->setupUi(this);

    mdiarea = MyQmdiArea::Instance(this);

    ui->txtMotivo->installEventFilter(this);

    ui->dtFechaInicio->setMinimumDate(fechainicial);
    ui->dtFechaFin->setMinimumDate(fechainicial);
    ui->dtFechaInicio->setDate(fechainicial);
    ui->dtFechaFin->setDate(fechainicial);

    ui->spDuracion->setValue(0);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarViaje()));
    connect(ui->btQuitarMotivo, SIGNAL(clicked(bool)), this, SLOT(quitarMotivo()));
    connect(ui->txtOrigen, SIGNAL(dobleclick()), this, SLOT(anadirOrigen()));
    connect(ui->txtDestino, SIGNAL(dobleclick()), this, SLOT(anadirDestino()));

    cargarModelos();
}

dlgViajeEntrada::~dlgViajeEntrada()
{
    delete ui;
}

void dlgViajeEntrada::aceptarViaje()
{
    Viaje viaje;

    viaje.setOriginal(ui->ckViajeInicial->checkState());
    viaje.setOrigen(lugar_origen_id);
    viaje.setDestino(lugar_destino_id);
    viaje.setMotivos(motivos);
    viaje.setMuerto(ui->ckMuerto->checkState());
    viaje.setMotivoMuerte(ui->txtMotivoMuerte->text());
    viaje.setLugarMuerte(ui->txtLugarMuerte->text());
    viaje.setFechaInicio(ui->dtFechaInicio->date());
    viaje.setFechaFin(ui->dtFechaFin->date());
    viaje.setDuracion(ui->spDuracion->value());
    viaje.setVuelta(ui->ckVuelta->checkState());

    if (ui->wdNotas->haCambiado())
        viaje.setNotas(ui->wdNotas->getNotas());

    emit(emitirViaje(viaje));
    cerrar();

}

void dlgViajeEntrada::anadirOrigen()
{
    dlgSeleccionarGeneral *seleccionar = new dlgSeleccionarGeneral(LUGAR, true, this);
    connect(seleccionar, SIGNAL(lugarEscogidoSignal(Lugar)), this, SLOT(recibirLugar(Lugar)));

    QMdiSubWindow *window = mdiarea->addSubWindow(seleccionar);
    window->show();
}

void dlgViajeEntrada::anadirDestino()
{
    dlgSeleccionarGeneral *seleccionar = new dlgSeleccionarGeneral(LUGAR, true, this);
    connect(seleccionar, SIGNAL(lugarEscogidoSignal(Lugar)), this, SLOT(recibirDestino(Lugar)));

    QMdiSubWindow *window = mdiarea->addSubWindow(seleccionar);
    window->show();
}

void dlgViajeEntrada::anadirMotivo()
{
    if (!ui->txtMotivo->text().isEmpty()){
        motivos.append(ui->txtMotivo->text());
        QListWidgetItem *item = new QListWidgetItem(ui->txtMotivo->text(), ui->twMotivos);
        ui->txtMotivo->setText("");
        ui->txtMotivo->setFocus();
    }
}

void dlgViajeEntrada::quitarMotivo()
{
    QModelIndex idx = ui->twMotivos->currentIndex();

    if (!idx.isValid())
        return;

    QString objeto = idx.data().toString();

    for (int i = 0; i < motivos.size(); ++i) {
        if (motivos.value(i) == objeto) {
            motivos.removeAt(i);
            break;
        }
    }

    ui->twMotivos->takeItem(ui->twMotivos->currentRow());

}

void dlgViajeEntrada::recibirLugar(Lugar lugar)
{
    lugar_origen_id = lugar.getId();
    ui->txtOrigen->setText(lugar.getLugar());
}

void dlgViajeEntrada::recibirDestino(Lugar lugar)
{
    lugar_destino_id = lugar.getId();
    ui->txtDestino->setText(lugar.getLugar());
}

void dlgViajeEntrada::cerrar()
{
    parentWidget()->close();
}

bool dlgViajeEntrada::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type()== QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
            if (keyEvent->key() == Qt::Key_Return){

                // y ahora dependiendo del QLineEdit...
                if (obj == ui->txtMotivo){
                    anadirMotivo();
                    return true;
            }
        }
    }

    /*
     * atención aquí lo importante es poner QWidget!
     * si pongo dlgPenaEntrada no funciona!!
     */
    return QWidget::eventFilter(obj, e);
}

void dlgViajeEntrada::cargarModelos()
{
    motivos_model = new QSqlQueryModel(this);
    motivos_model->setQuery(sql_motivos);

    motivos_completer = new QCompleter(motivos_model, this);
    motivos_completer->setCompletionColumn(0);
    motivos_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtMotivo->setCompleter(motivos_completer);

    motivos_muerte_model = new QSqlQueryModel(this);
    motivos_muerte_model->setQuery(sql_motivos_muerte);

    motivos_muerte_completer = new QCompleter(motivos_muerte_model, this);
    motivos_muerte_completer->setCompletionColumn(0);
    motivos_muerte_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtMotivoMuerte->setCompleter(motivos_muerte_completer);

    lugares_muerte_model = new QSqlQueryModel(this);
    lugares_muerte_model->setQuery(sql_lugares_muerte);

    lugares_muerte_completer = new QCompleter(lugares_muerte_model, this);
    lugares_muerte_completer->setCompletionColumn(0);
    lugares_muerte_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtLugarMuerte->setCompleter(lugares_muerte_completer);

}
