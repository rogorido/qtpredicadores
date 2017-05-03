#include "dlgpenaentrada.h"
#include "ui_dlgpenaentrada.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QListWidgetItem>
#include <QModelIndex>

#include <QDebug>

const QString sql_tipos="SELECT DISTINCT jsonb_array_elements_text(details->'pena_tipos') AS penas "
                             "FROM resolutions_details WHERE details->>'pena_tipos' IS NOT NULL "
                             "ORDER BY penas";
const QString sql_penatexto="SELECT DISTINCT details->>'pena_texto' AS pena_texto "
                            "FROM resolutions_details WHERE details ? 'pena' ORDER BY pena_texto";
const QString sql_penados="SELECT DISTINCT jsonb_array_elements_text(details->'penados') AS penados "
                             "FROM resolutions_details WHERE details->>'penados' IS NOT NULL "
                             "ORDER BY penados";
const QString sql_motivo="SELECT DISTINCT details->>'motivo' AS motivo "
                            "FROM resolutions_details WHERE details ? 'pena' ORDER BY motivo";

dlgPenaEntrada::dlgPenaEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgPenaEntrada)
{
    ui->setupUi(this);

    //connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->btEliminarPenas, SIGNAL(clicked(bool)), this, SLOT(quitarPenasTipos()));
    connect(ui->btEliminarPenados, SIGNAL(clicked(bool)), this, SLOT(quitarPenados()));

    activarTeclaReturn();

    cargarModelos();
}

dlgPenaEntrada::~dlgPenaEntrada()
{
    delete ui;
}

void dlgPenaEntrada::aceptar()
{
    ExtraInfos extras = ui->widget->getExtraInfos();

    pena.setPenasTipos(penastipos);
    pena.setDuracion(ui->txtDuracion->text());
    pena.setPenados(penados);
    pena.setSeguridad(ui->spSeguridad->value());
    pena.setMotivo(ui->txtMotivo->text());
    pena.setExtraInfos(extras);
    // TODO: falta penatexto!

    emit(aceptarPena(pena));

    close();
}

void dlgPenaEntrada::anadirPenasTipos()
{
    if (!ui->txtTipos->text().isEmpty()){
        qDebug() << "pulsado return...";
        penastipos.append(ui->txtTipos->text());
        QListWidgetItem *item = new QListWidgetItem(ui->txtTipos->text(), ui->lwTipos);
        ui->txtTipos->setText("");
    }
}

void dlgPenaEntrada::quitarPenasTipos()
{
    QModelIndex idx = ui->lwTipos->currentIndex();

    if (!idx.isValid())
        return;

    QString tipo = idx.data().toString();

    for (int i = 0; i < penastipos.size(); ++i) {
        if (penastipos.value(i) == tipo) {
            penastipos.removeAt(i);
            break;
        }
    }

    ui->lwTipos->takeItem(ui->lwTipos->currentRow());

}

void dlgPenaEntrada::anadirPenados()
{
    if (!ui->txtPenados->text().isEmpty()){
        penados.append(ui->txtPenados->text());
        QListWidgetItem *item = new QListWidgetItem(ui->txtPenados->text(), ui->lwPenados);
        ui->txtPenados->setText("");
    }
}

void dlgPenaEntrada::quitarPenados()
{
    QModelIndex idx = ui->lwPenados->currentIndex();

    if (!idx.isValid())
        return;

    QString penado = idx.data().toString();

    for (int i = 0; i < penados.size(); ++i) {
        if (penados.value(i) == penado) {
            penados.removeAt(i);
            break;
        }
    }

    ui->lwPenados->takeItem(ui->lwPenados->currentRow());


}

bool dlgPenaEntrada::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type()== QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
            if (keyEvent->key() == Qt::Key_Return){

                // y ahora dependiendo del QLineEdit...
                if (obj == ui->txtTipos){
                    anadirPenasTipos();
                    return true;
                }
                else if (obj == ui->txtPenados) {
                    anadirPenados();
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

void dlgPenaEntrada::cargarModelos()
{
    tipos_model = new QSqlQueryModel(this);
    tipos_model->setQuery(sql_tipos);

    tipos_completer = new QCompleter(tipos_model, this);
    tipos_completer->setCompletionColumn(0);
    tipos_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtTipos->setCompleter(tipos_completer);

    penados_model = new QSqlQueryModel(this);
    penados_model->setQuery(sql_penados);

    penados_completer = new QCompleter(penados_model, this);
    penados_completer->setCompletionColumn(0);
    penados_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtPenados->setCompleter(penados_completer);

    penatexto_model = new QSqlQueryModel(this);
    penatexto_model->setQuery(sql_penatexto);

    penatexto_completer = new QCompleter(penatexto_model, this);
    penatexto_completer->setCompletionColumn(0);
    penatexto_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtPenaTexto->setCompleter(penatexto_completer);

    motivo_model = new QSqlQueryModel(this);
    motivo_model->setQuery(sql_motivo);

    motivo_completer = new QCompleter(motivo_model, this);
    motivo_completer->setCompletionColumn(0);
    motivo_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtMotivo->setCompleter(motivo_completer);

}

void dlgPenaEntrada::activarTeclaReturn()
{
    ui->txtTipos->installEventFilter(this);
    ui->txtPenados->installEventFilter(this);
}
