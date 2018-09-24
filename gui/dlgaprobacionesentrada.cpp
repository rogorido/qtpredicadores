#include "dlgaprobacionesentrada.h"
#include "ui_dlgaprobacionesentrada.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QMessageBox>
#include <QMdiSubWindow>

#include "gui/dlgseleccionargeneral.h"
#include "widgets/myqmdiarea.h"

const QString sql_cargos="SELECT DISTINCT details->>'aprobación_cargo' AS cargo "
                         "FROM resolutions_details WHERE details ? 'aprobación' ORDER BY cargo";

const QString sql_institucion="SELECT DISTINCT details->>'tipo_institucion' AS institucion "
                         "FROM resolutions_details WHERE details ? 'aprobación' ORDER BY institucion";

const QString sql_librekeys = "SELECT DISTINCT jsonb_object_keys(details) as keys "
                              "FROM resolutions_details WHERE details ? 'aprobación' ORDER BY keys";

// con esto evitamos que dé números que son muy frecuentes en los values del jsonb details.
const QString sql_librevalues = "SELECT DISTINCT value FROM resolutions_details, jsonb_each_text(details) "
                                "WHERE details ? 'aprobación' AND value !~ '[0-9]'";

/*
 * TODO: estrictamente en el caso de las casas no debería ser
 * necesario que yo metiera la provincia. Tendría que hacer un método
 * en Casa::getProvinciaFromDB() para que cogiera la provincia
 * de la casa en cuestión...
 */

dlgAprobacionesEntrada::dlgAprobacionesEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgAprobacionesEntrada)
{
    ui->setupUi(this);

    mdiarea = MyQmdiArea::Instance(this);

    aprobacion_activa = new Aprobacion();
    aprobaciones_model = new AprobacionesTableModel(this);

    ui->twAprobaciones->setModel(aprobaciones_model);
    ui->twAprobaciones->setAlternatingRowColors(true);
    ui->twAprobaciones->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twAprobaciones->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twAprobaciones->horizontalHeader()->setStretchLastSection(true);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    connect(ui->btPersona, SIGNAL(clicked(bool)), this, SLOT(anadirPersona()));
    connect(ui->btProvincia, SIGNAL(clicked(bool)), this, SLOT(anadirProvincia()));
    connect(ui->btProvinciaInstitucion, SIGNAL(clicked(bool)), this, SLOT(anadirProvincia()));
    connect(ui->btCasa, SIGNAL(clicked(bool)), this, SLOT(anadirCasa()));
    connect(ui->btAnadirAprobacion, SIGNAL(clicked(bool)), this, SLOT(anadirAprobacion()));
    connect(ui->btQuitarAprobacion, SIGNAL(clicked(bool)), this, SLOT(quitarAprobacion()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarAprobaciones()));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabCambiado(int)));

    cargarModelos();

}

dlgAprobacionesEntrada::~dlgAprobacionesEntrada()
{
    delete ui;
}

void dlgAprobacionesEntrada::anadirAprobacion()
{
    /*
     * tenemos que comprobar qué tab está activo:
     * el de personas o el de instituciones...
     */

    if (tabSeleccionado == 0) { // el de personas
        if (ui->txtCargo->text().isEmpty()){
            int ret = QMessageBox::warning(this, "No hay texto en el tipo de aprobación",
                                           "Introduzca por favor texto en el tipo de aprobación");
            Q_UNUSED(ret)
            return;
        }
        aprobacion_activa->setTipoAprobacion(Aprobacion::TipoAprobacion::PERSONA);
        aprobacion_activa->setCargo(ui->txtCargo->text());
        aprobacion_activa->setPersona(persona_seleccionada);

        // borramos los campos
        ui->txtPersona->setText("");
        ui->txtProvincia->setText("");

        persona_seleccionada = Persona();
    }
    else if (tabSeleccionado == 1) { // el de instituciones
        if (ui->txtTipoInstitucion->text().isEmpty()){
            int ret = QMessageBox::warning(this, "No hay texto en el tipo de aprobación",
                                           "Introduzca por favor texto en el tipo de aprobación");
            Q_UNUSED(ret)
            return;
        }
        aprobacion_activa->setTipoAprobacion(Aprobacion::TipoAprobacion::CASA);
        aprobacion_activa->setCasa(casa_seleccionada);
        aprobacion_activa->setTipoInstitucion(ui->txtTipoInstitucion->text());

        // borramos los campos
        ui->txtCasa->setText("");
        ui->txtProvinciaInstitucion->setText("");

        casa_seleccionada = Casa();

    }

    // la provincia vale realmente para los dos tipos...
    aprobacion_activa->setProvincia(provincia_seleccionada);

    // y reinicializamos la provincia...
    provincia_seleccionada = Provincia();

    if (ui->wdNotas->haCambiado())
        aprobacion_activa->setNotas(ui->wdNotas->getNotas());

    ExtraInfos e = ui->wdExtras->getExtraInfos();
    aprobacion_activa->setExtraInfos(e);

    aprobaciones_model->anadirAprobacion(aprobacion_activa);

    // borramos la aprobación activa creando un nuevo objeto
    aprobacion_activa = new Aprobacion();

    ui->wdExtras->clear();
    ui->wdNotas->reiniciar();

    ui->twAprobaciones->resizeColumnsToContents();
    ui->twAprobaciones->resizeRowsToContents();

}

void dlgAprobacionesEntrada::quitarAprobacion()
{
    QModelIndex idx = ui->twAprobaciones->currentIndex();

    if (!idx.isValid())
        return;

    int row = idx.row();
    aprobaciones_model->quitarAprobacion(row);
}

void dlgAprobacionesEntrada::aceptarAprobaciones()
{
    QList<Aprobacion*> lista = aprobaciones_model->getLista();

    emit(aceptarDatos(lista));

    cerrar();
}

void dlgAprobacionesEntrada::anadirPersona()
{
    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(PERSONA, true, this);
    connect(dlgseleccionar, SIGNAL(personaEscogidaSignal(Persona)), this, SLOT(actualizarPersona(Persona)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgseleccionar);
    window->show();
}

void dlgAprobacionesEntrada::anadirProvincia()
{

    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(PROVINCIA, true, this);
    connect(dlgseleccionar, SIGNAL(provinciaEscogidaSignal(Provincia)), this, SLOT(actualizarProvincia(Provincia)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgseleccionar);
    window->show();
}

void dlgAprobacionesEntrada::anadirCasa()
{
    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(CASA, true, this);
    connect(dlgseleccionar, SIGNAL(casaEscogidaSignal(Casa)), this, SLOT(actualizarCasa(Casa)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgseleccionar);
    window->show();
}

void dlgAprobacionesEntrada::actualizarPersona(Persona persona)
{
    persona_seleccionada = persona;
    QString nombre_persona;

    nombre_persona = persona.getNombre() + ' ' + persona.getApellidos() + ' ' + persona.getOrigen();

    ui->txtPersona->setText(nombre_persona);
}

void dlgAprobacionesEntrada::actualizarProvincia(Provincia provincia)
{
    provincia_seleccionada = provincia;

    if (tabSeleccionado == 0)
        ui->txtProvincia->setText(provincia.getNombre());
    else
        ui->txtProvinciaInstitucion->setText(provincia.getNombre());
}

void dlgAprobacionesEntrada::actualizarCasa(Casa casa)
{
    casa_seleccionada = casa;
    ui->txtCasa->setText(casa.getNombre());
}

void dlgAprobacionesEntrada::tabCambiado(int t)
{
    Q_UNUSED(t)
    tabSeleccionado = ui->tabWidget->currentIndex();

    /*
     * esto es una cutrada, pero el asunto es el siguiente:
     * par meter los datos en el tableview lo decidimos dependiendo
     * de qué tab esté seleccionado. Pero si está seleccionado el 3º
     * el de datos extras, no puede saber si metemos instituciones o personas...
     * y por tanto deshabilito el pushbutton
     */
    switch (tabSeleccionado) {
    case 0:
        ui->btAnadirAprobacion->setEnabled(true);
        break;
    case 1:
        ui->btAnadirAprobacion->setEnabled(true);
        break;
    case 2: // esto es lo de ntoas...
        ui->btAnadirAprobacion->setEnabled(false);
        break;
    case 3: // esto es lo de ntoas...
        ui->btAnadirAprobacion->setEnabled(false);
        break;
    default:
        break;
    }
}

void dlgAprobacionesEntrada::cerrar()
{
    parentWidget()->close();
}

void dlgAprobacionesEntrada::cargarModelos()
{
    cargos_model = new QSqlQueryModel(this);
    cargos_model->setQuery(sql_cargos);

    cargos_completer = new QCompleter(cargos_model, this);
    cargos_completer->setCompletionColumn(0);
    cargos_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtCargo->setCompleter(cargos_completer);

    instituciones_model = new QSqlQueryModel(this);
    instituciones_model->setQuery(sql_institucion);

    instituciones_completer = new QCompleter(instituciones_model, this);
    instituciones_completer->setCompletionColumn(0);
    instituciones_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtTipoInstitucion->setCompleter(instituciones_completer);

    ui->wdExtras->recibirConsultasCompleter(sql_librekeys, sql_librevalues);
}
