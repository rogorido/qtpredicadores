#include "barralabel.h"

BarraLabel::BarraLabel(QWidget *parent) : QLabel(parent)
{

}

BarraLabel::~BarraLabel()
{

}

void BarraLabel::inicializar()
{
    crearTexto();
    this->setText(textomostrado);

}

void BarraLabel::crearTexto()
{
    QString texto_final;

    texto_final = "Casas: " + QString::number(n_casas);

    textomostrado = texto_final;

}
