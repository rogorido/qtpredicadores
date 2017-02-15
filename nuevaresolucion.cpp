#include "nuevaresolucion.h"
#include "ui_nuevaresolucion.h"

#include <QInputDialog>

#include "temas.h"

NuevaResolucion::NuevaResolucion(Temas *temas, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevaResolucion), m_temas(temas)
{
    ui->setupUi(this);

    rellenarCombos();
}

NuevaResolucion::~NuevaResolucion()
{
    delete ui;
}

void NuevaResolucion::rellenarCombos(){

    ui->cboTemas->setModel(m_temas);
    ui->cboTemas->setCurrentIndex(-1);
    ui->cboTemas->setModelColumn(1);

}

void NuevaResolucion::on_btNuevoTema_clicked(){

    QString tema;

    tema = QInputDialog::getText(this, "Introduzca nuevo tema", "Nueva tema");

    if (!tema.isEmpty())
        m_temas->AnadirTema(tema);

}
