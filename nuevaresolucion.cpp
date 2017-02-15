#include "nuevaresolucion.h"
#include "ui_nuevaresolucion.h"

#include "temas.h"

NuevaResolucion::NuevaResolucion(Temas *temas, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevaResolucion), m_temas(temas)
{
    ui->setupUi(this);
}

NuevaResolucion::~NuevaResolucion()
{
    delete ui;
}
