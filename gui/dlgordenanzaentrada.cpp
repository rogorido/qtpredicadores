#include "dlgordenanzaentrada.h"
#include "ui_dlgordenanzaentrada.h"

#include "gui/dlgpenaentrada.h"
#include "gui/dlgtemas.h"

#include "widgets/myqmdiarea.h"

#include <QSqlQueryModel>
#include <QCompleter>
// entiendo que estos no son necesarios pero bueno...
#include <QListWidgetItem>
#include <QModelIndex>
#include <QMdiSubWindow>

const QString sql_receptores="SELECT DISTINCT jsonb_array_elements_text(details->'destinatarios_pena') AS penados "
                             "FROM resolutions_details WHERE details->>'destinatarios_pena' IS NOT NULL "
                             "ORDER BY penados";
const QString sql_objetos="SELECT DISTINCT jsonb_array_elements_text(details->'objetos') AS objetos "
                             "FROM resolutions_details WHERE details->>'objetos' IS NOT NULL "
                             "ORDER BY objetos";

dlgOrdenanzaEntrada::dlgOrdenanzaEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgOrdenanzaEntrada)
{
    ui->setupUi(this);

    mdiarea = MyQmdiArea::Instance(this);

    ui->txtObjeto->installEventFilter(this);
    ui->txtReceptor->installEventFilter(this);

    ui->cbTipo->addItem("Prohibición", QVariant(1));
    ui->cbTipo->addItem("Mandato", QVariant(2));
    ui->cbTipo->addItem("Admonición", QVariant(3));
    ui->cbTipo->addItem("Comisión", QVariant(4));

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->btEliminarObjetos, SIGNAL(clicked(bool)), this, SLOT(quitarObjeto()));
    connect(ui->btEliminarReceptores, SIGNAL(clicked(bool)), this, SLOT(quitarReceptor()));
    connect(ui->btPenas, SIGNAL(clicked(bool)), this, SLOT(anadirPena()));
    connect(ui->wdNotas, SIGNAL(textoIntroducido()), this, SLOT(notaIntroducida()));

}

dlgOrdenanzaEntrada::~dlgOrdenanzaEntrada()
{
    delete ui;
}

bool dlgOrdenanzaEntrada::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type()== QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
            if (keyEvent->key() == Qt::Key_Return){

                // y ahora dependiendo del QLineEdit...
                if (obj == ui->txtObjeto){
                    anadirObjeto();
                    return true;
                }
                else if (obj == ui->txtReceptor) {
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

void dlgOrdenanzaEntrada::cargarModelos()
{
    receptores_model = new QSqlQueryModel(this);
    receptores_model->setQuery(sql_receptores);

    receptores_completer = new QCompleter(receptores_model, this);
    receptores_completer->setCompletionColumn(0);
    receptores_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtReceptor->setCompleter(receptores_completer);

    objetos_model = new QSqlQueryModel(this);
    objetos_model->setQuery(sql_objetos);

    objetos_completer = new QCompleter(objetos_model, this);
    objetos_completer->setCompletionColumn(0);
    objetos_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtObjeto->setCompleter(objetos_completer);
}

void dlgOrdenanzaEntrada::aceptar() {

    if (ui->cbTipo->currentText() == "Prohibición")
        ordenanza.setTipo(Ordenanza::TipoOrdenanza::PROHIBICION);
    else if (ui->cbTipo->currentText() == "Mandato")
        ordenanza.setTipo(Ordenanza::TipoOrdenanza::MANDATO);
    else if (ui->cbTipo->currentText() == "Comisión")
        ordenanza.setTipo(Ordenanza::TipoOrdenanza::COMISION);
    else
        ordenanza.setTipo(Ordenanza::TipoOrdenanza::ADMONICION);

    ordenanza.setObjetos(lista_objetos);
    ordenanza.setReceptores(lista_receptores);
    ordenanza.setPena(pena_estipulada);
    ordenanza.setRestriccion(ui->txtRestriccion->text());
    ordenanza.setSeguridad(ui->spSeguridad->value());

    ExtraInfos e = ui->widget->getExtraInfos();
    ordenanza.setExtraInfos(e);

    if (ui->ckRetro->checkState() == Qt::Checked){
        RetroReferencia retro;

        retro.setTipo(ui->txtRetroTipo->text());
        retro.setReferencia(ui->txtReferencia->text());
        retro.setTextoReal(ui->txtTextoReal->text());

        ordenanza.setRetroReferencia(retro);
    }

    if (temas_lista.size() > 0) {
        QList<int> temas_id;

        for (int i = 0; i < temas_lista.size(); ++i) {
            temas_id.append(temas_lista.at(i).id);
        }

        ordenanza.setTemas(temas_id);
    }

    if (ui->wdNotas->haCambiado())
        ordenanza.setNota(ui->wdNotas->getNotas());

    emit(aceptarOrdenanza(ordenanza));

    close();

}

void dlgOrdenanzaEntrada::anadirObjeto()
{
    if (!ui->txtObjeto->text().isEmpty()){
        lista_objetos.append(ui->txtObjeto->text());
        QListWidgetItem *item = new QListWidgetItem(ui->txtObjeto->text(), ui->lwObjetos);
        ui->txtObjeto->setText("");
    }

}

void dlgOrdenanzaEntrada::anadirReceptor()
{
    if (!ui->txtReceptor->text().isEmpty()){
        lista_receptores.append(ui->txtReceptor->text());
        QListWidgetItem *item = new QListWidgetItem(ui->txtReceptor->text(), ui->lwReceptores);
        ui->txtReceptor->setText("");
    }

}

void dlgOrdenanzaEntrada::quitarObjeto()
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

void dlgOrdenanzaEntrada::quitarReceptor()
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

void dlgOrdenanzaEntrada::anadirPena()
{
    dlgPenaEntrada *dlgpena = new dlgPenaEntrada(this);
    dlgpena->show();

    connect(dlgpena, SIGNAL(aceptarPena(Pena)), this, SLOT(recibirPena(Pena)));
}

void dlgOrdenanzaEntrada::recibirPena(Pena pena)
{
    pena_estipulada = pena;

}

void dlgOrdenanzaEntrada::on_btTemas_clicked()
{
    dlgtemas = new dlgTemas(&temas_lista, this);
    QMdiSubWindow *window = mdiarea->addSubWindow(dlgtemas);
    window->show();

}

void dlgOrdenanzaEntrada::cerrar()
{
    parentWidget()->close();
}

