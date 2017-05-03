#include "dlgordenanzaentrada.h"
#include "ui_dlgordenanzaentrada.h"

dlgOrdenanzaEntrada::dlgOrdenanzaEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgOrdenanzaEntrada)
{
    ui->setupUi(this);

    ui->txtObjeto->installEventFilter(this);
    ui->txtReceptor->installEventFilter(this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
}

dlgOrdenanzaEntrada::~dlgOrdenanzaEntrada()
{
    delete ui;
}

bool dlgOrdenanzaEntrada::eventFilter(QObject *obj, QEvent *e)
{

    return QDialog::eventFilter(obj, e);
}

void dlgOrdenanzaEntrada::aceptar() {

}

void dlgOrdenanzaEntrada::anadirObjeto()
{
    if (!ui->txtObjeto->text().isEmpty()){
        objetos.append(ui->txtObjeto->text());
        QListWidgetItem *item = new QListWidgetItem(ui->txtObjeto->text(), ui->lwObjetos);
        ui->txtObjeto->setText("");
    }

}
