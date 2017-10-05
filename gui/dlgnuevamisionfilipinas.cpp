#include "dlgnuevamisionfilipinas.h"
#include "ui_dlgnuevamisionfilipinas.h"

#include <QMessageBox>
#include <QMdiSubWindow>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

#include "models/qjsonmodel.h"
#include "models/misionesmodel.h"
#include "widgets/myqmdiarea.h"
#include "objs/notas.h"
#include "objs/mision.h"
#include "dlgseleccionargeneral.h"

const QDate fechainicial = QDate(1200, 1, 1);
const QDate fechafinal = QDate(1800, 1, 1);

dlgNuevaMisionFilipinas::dlgNuevaMisionFilipinas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaMisionFilipinas)
{
    ui->setupUi(this);
    mdiarea = MyQmdiArea::Instance(this);

    m_misiones = MisionesModel::InstanceModel();

    json_etapas = new QJsonModel(this);
    ui->twEtapas->setModel(json_etapas);

    ui->dtFechaInicio->setMinimumDate(fechainicial);
    ui->dtFechaInicio->setMaximumDate(fechafinal);
    ui->dtFechaFin->setMinimumDate(fechainicial);
    ui->dtFechaFin->setMaximumDate(fechafinal);
    ui->dtFechaInicio->setDate(fechainicial);

    ui->dtFechaInicioEtapa->setMinimumDate(fechainicial);
    ui->dtFechaInicioEtapa->setMaximumDate(fechafinal);
    ui->dtFechaFinEtapa->setMinimumDate(fechainicial);
    ui->dtFechaFinEtapa->setMaximumDate(fechafinal);
    ui->dtFechaInicioEtapa->setDate(fechainicial);

    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(cerrar()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarMision()));
    connect(ui->txtLugarSalida, SIGNAL(dobleclick()), this, SLOT(anadirSalidaMision()));
    connect(ui->txtSalidaEtapa, SIGNAL(dobleclick()), this, SLOT(anadirSalidaEtapa()));
    connect(ui->txtLlegadaEtapa, SIGNAL(dobleclick()), this, SLOT(anadirLlegadaEtapa()));
    connect(ui->btAnadir, SIGNAL(clicked(bool)), this, SLOT(anadirEtapa()));
}

dlgNuevaMisionFilipinas::~dlgNuevaMisionFilipinas()
{
    delete ui;
}

void dlgNuevaMisionFilipinas::aceptarMision()
{

}

void dlgNuevaMisionFilipinas::anadirLugarGeneral()
{
    dlgSeleccionarGeneral *seleccionar = new dlgSeleccionarGeneral(LUGAR, this);
    connect(seleccionar, SIGNAL(lugarEscogidoSignal(Lugar)), this, SLOT(recibirLugarSlot(Lugar)));

    QMdiSubWindow *window = mdiarea->addSubWindow(seleccionar);
    window->show();
}

void dlgNuevaMisionFilipinas::anadirSalidaMision()
{
    tipolugar_pulsado = TipoLugar::SALIDAMISION;
    anadirLugarGeneral();
}

void dlgNuevaMisionFilipinas::anadirSalidaEtapa()
{
    tipolugar_pulsado = TipoLugar::SALIDAETAPA;
    anadirLugarGeneral();
}

void dlgNuevaMisionFilipinas::anadirLlegadaEtapa()
{
    tipolugar_pulsado = TipoLugar::LLEGADAETAPA;
    anadirLugarGeneral();
}


void dlgNuevaMisionFilipinas::anadirEtapa()
{
    /*
     * necesitamos dos pq las etapas van metidas en un
     * json con el nombre etapa1: {etc}, etapa2: {ec}
     */
    QJsonObject etapa_general;
    QJsonObject etapa_concreta;
    QString nombre_etapa; // lo construimos...

    int numero_etapa = ui->spNumeroEtapa->value();
    // el lugar_salida_etapa y lugar_llegada_etapa son generales
    QDate fecha_salida = ui->dtFechaInicioEtapa->date();
    QDate fecha_llegada = ui->dtFechaFinEtapa->date();

    etapa_concreta.insert("numero", QJsonValue(numero_etapa));
    etapa_concreta.insert("lugar_salida", QJsonValue(lugarsalida_etapa_id));
    etapa_concreta.insert("lugar_llegada", QJsonValue(lugarllegada_etapa_id));
    etapa_concreta.insert("fecha_salida", fecha_salida.toString());
    etapa_concreta.insert("fecha_llegada", fecha_llegada.toString());

    nombre_etapa = "etapa" + QString::number(numero_etapa);

    etapa_general.insert(nombre_etapa, etapa_concreta);

    json_etapas->anadirJson(etapa_general);
    json_etapas->resetearModelo();

    borrarCamposEtapa();

}

void dlgNuevaMisionFilipinas::recibirLugarSlot(Lugar lugar)
{
    switch (tipolugar_pulsado) {
    case TipoLugar::SALIDAMISION:
        lugarsalida_mision_id = lugar.getId();
        ui->txtLugarSalida->setText(lugar.getLugar());
        break;
    case TipoLugar::SALIDAETAPA:
        lugarsalida_etapa_id = lugar.getId();
        ui->txtSalidaEtapa->setText(lugar.getLugar());
        break;
    case TipoLugar::LLEGADAETAPA:
        lugarllegada_etapa_id = lugar.getId();
        ui->txtLlegadaEtapa->setText(lugar.getLugar());
        break;
    default:
        break;
    }

}

void dlgNuevaMisionFilipinas::cerrar()
{
    parentWidget()->close();
}

void dlgNuevaMisionFilipinas::borrarCamposEtapa()
{
    int etapa = ui->spNumeroEtapa->value() + 1;
    ui->spNumeroEtapa->setValue(etapa);

    lugarsalida_etapa_id = 0;
    lugarllegada_etapa_id = 0;
    ui->txtSalidaEtapa->setText("");
    ui->txtLlegadaEtapa->setText("");
    ui->dtFechaInicioEtapa->setDate(fechainicial);
    ui->dtFechaFinEtapa->setDate(fechafinal);
}
