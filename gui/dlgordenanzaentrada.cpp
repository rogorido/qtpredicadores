#include "dlgordenanzaentrada.h"
#include "ui_dlgordenanzaentrada.h"

#include "gui/dlgpenaentrada.h"

dlgOrdenanzaEntrada::dlgOrdenanzaEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgOrdenanzaEntrada)
{
    ui->setupUi(this);

    ui->txtObjeto->installEventFilter(this);
    ui->txtReceptor->installEventFilter(this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->btEliminarObjetos, SIGNAL(clicked(bool)), this, SLOT(quitarObjeto()));
    connect(ui->btEliminarReceptores, SIGNAL(clicked(bool)), this, SLOT(quitarReceptor()));
    connect(ui->btPenas, SIGNAL(clicked(bool)), this, SLOT(anadirPena()));
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

void dlgOrdenanzaEntrada::aceptar() {

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
