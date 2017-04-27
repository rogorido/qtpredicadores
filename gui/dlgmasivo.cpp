#include "dlgmasivo.h"
#include "ui_dlgmasivo.h"

dlgMasivo::dlgMasivo(JsonGestor *json, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgMasivo), jsondetalles(json)
{
    ui->setupUi(this);
}

dlgMasivo::~dlgMasivo()
{
    delete ui;
}
