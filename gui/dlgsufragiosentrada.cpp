#include "dlgsufragiosentrada.h"
#include "ui_dlgsufragiosentrada.h"

#include <QSqlQueryModel>
#include <QCompleter>

#include "objs/variados.h"

const QString sql_destinatarios="SELECT DISTINCT jsonb_array_elements_text(details->'destinatarios') AS destinatarios "
                                "FROM resolutions_details WHERE details ? 'sufragio' "
                                "ORDER BY destinatarios";

dlgSufragiosEntrada::dlgSufragiosEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSufragiosEntrada)
{
    ui->setupUi(this);

    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarSufragio()));
    connect(ui->btEliminar, SIGNAL(clicked(bool)), this, SLOT(quitarDestinatario()));

    ui->cbTipo->addItem("Por vivos");
    ui->cbTipo->addItem("Por muertos");

    ui->txtDestinatarios->installEventFilter(this);

    cargarModelos();
}

dlgSufragiosEntrada::~dlgSufragiosEntrada()
{
    delete ui;
}

bool dlgSufragiosEntrada::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == ui->txtDestinatarios)
    {
        if (e->type()==QEvent::KeyPress){
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
            if (keyEvent->key()==Qt::Key_Return || (keyEvent->key()==Qt::Key_Tab && !ui->txtDestinatarios->text().isEmpty())){
                anadirDestinatario();
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

void dlgSufragiosEntrada::aceptarSufragio()
{
    ExtraInfos extras = ui->wdExtras->getExtraInfos();

    sufragio.setTipo(ui->cbTipo->currentText());
    sufragio.setMotivo(ui->txtMotivo->text());
    sufragio.setMisas(ui->spMisas->value());
    sufragio.setExtraInfos(extras);

    emit(emitirSufragio(sufragio));

    close();
}

void dlgSufragiosEntrada::anadirDestinatario()
{
    if (!ui->txtDestinatarios->text().isEmpty()){
        destinatarios.append(ui->txtDestinatarios->text());
        QListWidgetItem *item = new QListWidgetItem(ui->txtDestinatarios->text(), ui->lwDestinatarios);
        // por qué coño no funciona esto o funciona erráticamente???
        ui->txtDestinatarios->setText("");
    }


}

void dlgSufragiosEntrada::quitarDestinatario()
{
    QModelIndex idx = ui->lwDestinatarios->currentIndex();

    if (!idx.isValid())
        return;

    QString destinatario = idx.data().toString();

    for (int i = 0; i < destinatarios.size(); ++i) {
        if (destinatarios.value(i) == destinatario) {
            destinatarios.removeAt(i);
            break;
        }
    }

    ui->lwDestinatarios->takeItem(ui->lwDestinatarios->currentRow());

}

void dlgSufragiosEntrada::cargarModelos()
{
    destinatarios_model = new QSqlQueryModel(this);
    destinatarios_model->setQuery(sql_destinatarios);

    destinatarios_completer = new QCompleter(destinatarios_model, this);
    destinatarios_completer->setCompletionColumn(0);
    destinatarios_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtDestinatarios->setCompleter(destinatarios_completer);

}
