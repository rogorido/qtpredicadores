#include "dlgordenanzaentrada.h"
#include "ui_dlgordenanzaentrada.h"

dlgOrdenanzaEntrada::dlgOrdenanzaEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgOrdenanzaEntrada)
{
    ui->setupUi(this);
}

dlgOrdenanzaEntrada::~dlgOrdenanzaEntrada()
{
    delete ui;
}

bool dlgOrdenanzaEntrada::eventFilter(QObject *obj, QEvent *e)
{

}
