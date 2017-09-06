#include "dlgdeclaraciongeneralentrada.h"
#include "ui_dlgdeclaraciongeneralentrada.h"

#include "gui/dlgpenaentrada.h"
#include "gui/dlgtemas.h"

#include "widgets/myqmdiarea.h"

#include <QSqlQueryModel>
#include <QCompleter>
// entiendo que estos no son necesarios pero bueno...
#include <QListWidgetItem>
#include <QModelIndex>
#include <QMdiSubWindow>

const QString sql_instituciones="SELECT DISTINCT jsonb_array_elements_text(details->'destinatarios_pena') AS penados "
                             "FROM resolutions_details WHERE details->>'destinatarios_pena' IS NOT NULL "
                             "ORDER BY penados";
const QString sql_cargos="SELECT DISTINCT jsonb_array_elements_text(details->'objetos') AS objetos "
                             "FROM resolutions_details WHERE details->>'objetos' IS NOT NULL "
                             "ORDER BY objetos";

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
    connect(ui->btEliminarCargos, SIGNAL(clicked(bool)), this, SLOT(quitarCargo()));
    connect(ui->btEliminarInstitucion, SIGNAL(clicked(bool)), this, SLOT(quitarInstitucion()));
    connect(ui->wdNotas, SIGNAL(textoIntroducido()), this, SLOT(notaIntroducida()));

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

    declaracion.setObjetos(lista_objetos);
    declaracion.setReceptores(lista_receptores);
    declaracion.setPena(pena_estipulada);
    declaracion.setRestriccion(ui->txtRestriccion->text());
    declaracion.setSeguridad(ui->spSeguridad->value());

    ExtraInfos e = ui->widget->getExtraInfos();
    declaracion.setExtraInfos(e);

    if (ui->ckRetro->checkState() == Qt::Checked){
        RetroReferencia retro;

        retro.setTipo(ui->txtRetroTipo->text());
        retro.setReferencia(ui->txtReferencia->text());
        retro.setTextoReal(ui->txtTextoReal->text());

        declaracion.setRetroReferencia(retro);
    }

    if (temas_lista.size() > 0) {
        QList<int> temas_id;

        for (int i = 0; i < temas_lista.size(); ++i) {
            temas_id.append(temas_lista.at(i).id);
        }

        declaracion.setTemas(temas_id);
    }

    if (ui->wdNotas->haCambiado())
        declaracion.setNota(ui->wdNotas->getNotas());

    emit(aceptardeclaracion(declaracion));

    close();

}

void dlgDeclaracionGeneralEntrada::anadirCargo()
{
    if (!ui->txtObjeto->text().isEmpty()){
        lista_objetos.append(ui->txtObjeto->text());
        QListWidgetItem *item = new QListWidgetItem(ui->txtObjeto->text(), ui->lwObjetos);
        ui->txtObjeto->setText("");
    }

}

void dlgDeclaracionGeneralEntrada::anadirInstitucion()
{
    if (!ui->txtReceptor->text().isEmpty()){
        lista_receptores.append(ui->txtReceptor->text());
        QListWidgetItem *item = new QListWidgetItem(ui->txtReceptor->text(), ui->lwReceptores);
        ui->txtReceptor->setText("");
    }

}

void dlgDeclaracionGeneralEntrada::quitarCargo()
{
    QModelIndex idx = ui->lwObjetos->currentIndex();

    if (!idx.isValid())
        return;

    QString objeto = idx.data().toString();

    for (int i = 0; i < lista_objetos.size(); ++i) {
        if (lista_objetos.value(i) == objeto) {
            lista_objetos.removeAt(i);
            break;
        }
    }

    ui->lwObjetos->takeItem(ui->lwObjetos->currentRow());
}

void dlgDeclaracionGeneralEntrada::quitarInstitucion()
{
    QModelIndex idx = ui->lwReceptores->currentIndex();

    if (!idx.isValid())
        return;

    QString receptor = idx.data().toString();

    for (int i = 0; i < lista_receptores.size(); ++i) {
        if (lista_receptores.value(i) == receptor) {
            lista_receptores.removeAt(i);
            break;
        }
    }

    ui->lwReceptores->takeItem(ui->lwReceptores->currentRow());
}

void dlgDeclaracionGeneralEntrada::cerrar()
{
    parentWidget()->close();
}

