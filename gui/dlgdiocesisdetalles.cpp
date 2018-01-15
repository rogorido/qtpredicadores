#include "dlgdiocesisdetalles.h"
#include "ui_dlgdiocesisdetalles.h"

dlgDiocesisDetalles::dlgDiocesisDetalles(int diocesis_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgDiocesisDetalles),
    dioc_id(diocesis_id)
{
    ui->setupUi(this);
}

dlgDiocesisDetalles::~dlgDiocesisDetalles()
{
    delete ui;
}
