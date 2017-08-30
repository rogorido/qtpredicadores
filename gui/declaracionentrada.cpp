#include "declaracionentrada.h"
#include "ui_declaracionentrada.h"

DeclaracionEntrada::DeclaracionEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeclaracionEntrada)
{
    ui->setupUi(this);
}

DeclaracionEntrada::~DeclaracionEntrada()
{
    delete ui;
}
