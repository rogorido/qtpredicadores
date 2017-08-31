#include "dlginfraccionentrada.h"
#include "ui_dlginfraccionentrada.h"

dlgInfraccionEntrada::dlgInfraccionEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgInfraccionEntrada)
{
    ui->setupUi(this);

    ui->txtInfractor->installEventFilter(this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->btEliminar, SIGNAL(clicked(bool)), this, SLOT(quitarInfractor()));

}

dlgInfraccionEntrada::~dlgInfraccionEntrada()
{
    delete ui;
}

void dlgInfraccionEntrada::aceptar()
{
    infraccion.setTipo(ui->txtTipo->text());

    // qué pasa si la infracción está vacía?
    infraccion.setInfraccion(ui->txtInfraccion->text());
    infraccion.setInfractores(lista_infractores);

    ExtraInfos e = ui->wdExtras->getExtraInfos();
    infraccion.setExtras(e);

    if (ui->wdNotas->haCambiado())
        infraccion.setNota(ui->wdNotas->getNotas());

    emit(aceptarInfraccion(infraccion));

    close();
}

void dlgInfraccionEntrada::anadirInfractor()
{
    if (!ui->txtInfractor->text().isEmpty()){
        lista_infractores.append(ui->txtInfractor->text());
        QListWidgetItem *item = new QListWidgetItem(ui->txtInfractor->text(), ui->lwInfractores);
        ui->txtInfractor->setText("");
    }
}

void dlgInfraccionEntrada::quitarInfractor()
{
    QModelIndex idx = ui->lwInfractores->currentIndex();

    if (!idx.isValid())
        return;

    QString infractor = idx.data().toString();

    for (int i = 0; i < lista_infractores.size(); ++i) {
        if (lista_infractores.value(i) == infractor) {
            lista_infractores.removeAt(i);
            break;
        }
    }

    ui->lwInfractores->takeItem(ui->lwInfractores->currentRow());
}

bool dlgInfraccionEntrada::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type()== QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
            if (keyEvent->key() == Qt::Key_Return){

                anadirInfractor();
                return true;
            }
        }

    /*
     * atención aquí lo importante es poner QDialog!
     * si pongo dlgPenaEntrada no funciona!!
     */
    return QDialog::eventFilter(obj, e);
}
