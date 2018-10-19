#include "dlgdeclaraciongeneralentrada.h"
#include "ui_dlgdeclaraciongeneralentrada.h"

#include "dlgseleccionargeneral.h"
#include "src/widgets/myqmdiarea.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QListWidgetItem>
#include <QModelIndex>
#include <QMdiSubWindow>

const QString sql_instituciones="SELECT DISTINCT jsonb_array_elements_text(details->'instituciones') AS instituciones "
                             "FROM resolutions_details WHERE details->>'instituciones' IS NOT NULL "
                             "ORDER BY instituciones";
const QString sql_cargos="SELECT DISTINCT jsonb_array_elements_text(details->'cargos') AS cargos "
                             "FROM resolutions_details WHERE details->>'cargos' IS NOT NULL "
                             "ORDER BY cargos";

dlgDeclaracionGeneralEntrada::dlgDeclaracionGeneralEntrada(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgDeclaracionGeneralEntrada)
{
    ui->setupUi(this);

    mdiarea = MyQmdiArea::Instance(this);

    ui->txtCargo->installEventFilter(this);
    ui->txtInstitucion->installEventFilter(this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->txtProvincia, SIGNAL(dobleclick()), this, SLOT(anadirProvincia()));
    connect(ui->btEliminarCargos, SIGNAL(clicked(bool)), this, SLOT(quitarCargo()));
    connect(ui->btEliminarInstitucion, SIGNAL(clicked(bool)), this, SLOT(quitarInstitucion()));
    connect(ui->btEliminarProvincias, SIGNAL(clicked(bool)), this, SLOT(quitarProvincia()));
    connect(ui->wdNotas, SIGNAL(textoIntroducido()), this, SLOT(notaIntroducida()));

    cargarModelos();

}

dlgDeclaracionGeneralEntrada::~dlgDeclaracionGeneralEntrada()
{
    delete ui;
}

bool dlgDeclaracionGeneralEntrada::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type()== QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
            if (keyEvent->key() == Qt::Key_Return){

                // y ahora dependiendo del QLineEdit...
                if (obj == ui->txtCargo){
                    anadirCargo();
                    return true;
                }
                else if (obj == ui->txtInstitucion) {
                    anadirInstitucion();
                    return true;
                }
            }
        }

    /*
     * atención aquí lo importante es poner QDialog!
     * si pongo dlgPenaEntrada no funciona!!
     */
    return QWidget::eventFilter(obj, e);
}

void dlgDeclaracionGeneralEntrada::cargarModelos()
{
    cargos_model = new QSqlQueryModel(this);
    cargos_model->setQuery(sql_cargos);

    cargos_completer = new QCompleter(cargos_model, this);
    cargos_completer->setCompletionColumn(0);
    cargos_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtCargo->setCompleter(cargos_completer);

    instituciones_model = new QSqlQueryModel(this);
    instituciones_model->setQuery(sql_instituciones);

    instituciones_completer = new QCompleter(instituciones_model, this);
    instituciones_completer->setCompletionColumn(0);
    instituciones_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtInstitucion->setCompleter(instituciones_completer);
}

void dlgDeclaracionGeneralEntrada::aceptar() {

    declaracion.setCargos(lista_cargos);
    declaracion.setInstituciones(lista_instituciones);
    declaracion.setProvincias(lista_provincias);

    ExtraInfos e = ui->widget->getExtraInfos();
    declaracion.setExtraInfos(e);

    if (ui->ckRetro->checkState() == Qt::Checked){
        RetroReferencia retro;

        retro.setTipo(ui->txtRetroTipo->text());
        retro.setReferencia(ui->txtReferencia->text());
        retro.setTextoReal(ui->txtTextoReal->text());

        declaracion.setRetroReferencia(retro);
    }

    if (ui->wdNotas->haCambiado())
        declaracion.setNota(ui->wdNotas->getNotas());

    emit(aceptarDeclaracion(declaracion));

    close();

}

void dlgDeclaracionGeneralEntrada::anadirCargo()
{
    if (!ui->txtCargo->text().isEmpty()){
        lista_cargos.append(ui->txtCargo->text());
        QListWidgetItem *item = new QListWidgetItem(ui->txtCargo->text(), ui->lwCargos);
        ui->txtCargo->setText("");
    }

}

void dlgDeclaracionGeneralEntrada::anadirInstitucion()
{
    if (!ui->txtInstitucion->text().isEmpty()){
        lista_instituciones.append(ui->txtInstitucion->text());
        QListWidgetItem *item = new QListWidgetItem(ui->txtInstitucion->text(), ui->lwInstitucion);
        ui->txtInstitucion->setText("");
    }

}

void dlgDeclaracionGeneralEntrada::anadirProvincia()
{
    dlgSeleccionarGeneral *dlgseleccionar = new dlgSeleccionarGeneral(PROVINCIA, true, this);
    connect(dlgseleccionar, SIGNAL(provinciaEscogidaSignal(Provincia)), this, SLOT(recibirProvincia(Provincia)));

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgseleccionar);
    window->show();
}

void dlgDeclaracionGeneralEntrada::quitarCargo()
{
    QModelIndex idx = ui->lwCargos->currentIndex();

    if (!idx.isValid())
        return;

    QString objeto = idx.data().toString();

    for (int i = 0; i < lista_cargos.size(); ++i) {
        if (lista_cargos.value(i) == objeto) {
            lista_cargos.removeAt(i);
            break;
        }
    }

    ui->lwCargos->takeItem(ui->lwCargos->currentRow());
}

void dlgDeclaracionGeneralEntrada::quitarInstitucion()
{
    QModelIndex idx = ui->lwInstitucion->currentIndex();

    if (!idx.isValid())
        return;

    QString institucion = idx.data().toString();

    for (int i = 0; i < lista_instituciones.size(); ++i) {
        if (lista_instituciones.value(i) == institucion) {
            lista_instituciones.removeAt(i);
            break;
        }
    }

    ui->lwInstitucion->takeItem(ui->lwInstitucion->currentRow());
}

void dlgDeclaracionGeneralEntrada::quitarProvincia()
{
    QModelIndex idx = ui->lwProvincias->currentIndex();

    if (!idx.isValid())
        return;

    int row = ui->lwProvincias->currentRow();
    lista_provincias.removeAt(row);
    ui->lwProvincias->takeItem(ui->lwProvincias->currentRow());
}

void dlgDeclaracionGeneralEntrada::recibirProvincia(Provincia provincia)
{
    lista_provincias.append(provincia.getId());
    QListWidgetItem *item = new QListWidgetItem(provincia.getNombre(), ui->lwProvincias);

}

void dlgDeclaracionGeneralEntrada::cerrar()
{
    parentWidget()->close();
}

