#include "dlgseleccionarpersona.h"
#include "ui_dlgseleccionarpersona.h"

dlgSeleccionarPersona::dlgSeleccionarPersona(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSeleccionarPersona)
{
    ui->setupUi(this);
}

dlgSeleccionarPersona::~dlgSeleccionarPersona()
{
    delete ui;
}
