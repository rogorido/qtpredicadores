#include "dlgreforma.h"
#include "ui_dlgreforma.h"

dlgReforma::dlgReforma(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgReforma)
{
    ui->setupUi(this);

    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(close()));

}

dlgReforma::~dlgReforma()
{
    delete ui;
}
