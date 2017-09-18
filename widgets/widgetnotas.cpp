#include "widgetnotas.h"
#include "ui_widgetnotas.h"

WidgetNotas::WidgetNotas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetNotas)
{
    ui->setupUi(this);
}

WidgetNotas::~WidgetNotas()
{
    delete ui;
}

void WidgetNotas::reiniciar()
{
    ui->txtNota->setText("");
    ui->ckInteresante->setCheckState(Qt::Unchecked);
    ui->ckVolverMirar->setCheckState(Qt::Unchecked);
    ui->spSeguridad->setValue(100);
}

bool WidgetNotas::haCambiado()
{
    /*
     * el valor básico de seguridad es 100
     */
    if (ui->ckVolverMirar->checkState() == Qt::Checked ||
            ui->ckInteresante->checkState() == Qt::Checked ||
            ui->txtNota->toPlainText() != "" ||
            ui->spSeguridad->value() != 100)
        return true;
    else
        return false;
}

Notas WidgetNotas::getNotas()
{
    nota.setVolverMirar(ui->ckVolverMirar->checkState());
    nota.setInteresante(ui->ckInteresante->checkState());
    nota.setNota(ui->txtNota->toPlainText());
    nota.setSeguridad(ui->spSeguridad->value());

    return nota;
}
