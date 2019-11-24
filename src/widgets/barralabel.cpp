#include "barralabel.h"

BarraLabel::BarraLabel(QWidget *parent) : QLabel(parent) {}

BarraLabel::~BarraLabel() {}

void BarraLabel::inicializar()
{
  crearTexto();
  this->setText(textomostrado);
}

void BarraLabel::setNumeroObisposFiltrados(const int n)
{
  f_obispos = n;
  inicializar();
}

void BarraLabel::setNumeroObrasFiltrados(const int n)
{
  f_obras = n;
  inicializar();
}

void BarraLabel::setNumeroPersonasFiltrados(const int n)
{
  f_personas = n;
  inicializar();
}

void BarraLabel::setNumeroCasasFiltrados(const int n)
{
  f_casas = n;
  inicializar();
}

void BarraLabel::setNumeroCiudadesFiltrados(const int n)
{
  f_ciudades = n;
  inicializar();
}

void BarraLabel::crearTexto()
{
  QString texto_final;

  if (n_personas == f_personas)
    texto_final = "Personas: " + QString::number(n_personas);
  else
    texto_final = "Personas: " + QString::number(f_personas) + QString("/") +
                  QString::number(n_personas);

  texto_final += "    ";

  if (n_casas == f_casas)
    texto_final += "Casas: " + QString::number(n_casas);
  else
    texto_final += "Casas: " + QString::number(f_casas) + QString("/") +
                   QString::number(n_casas);

  texto_final += "    ";

  if (n_ciudades == f_ciudades)
    texto_final += "Ciudades: " + QString::number(n_ciudades);
  else
    texto_final += "Ciudades: " + QString::number(f_ciudades) + QString("/") +
                   QString::number(n_ciudades);

  texto_final += "    ";

  if (n_obras == f_obras)
    texto_final += "Obras: " + QString::number(n_obras);
  else
    texto_final += "Obras: " + QString::number(f_obras) + QString("/") +
                   QString::number(n_obras);

  textomostrado = texto_final;
}
