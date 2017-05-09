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

bool WidgetNotas::haCambiado()
{
    if (ui->ckVolverMirar->checkState() == Qt::Checked || ui->txtNota->toPlainText() != "")
        return true;
    else
        return false;
}

Notas WidgetNotas::getNotas()
{
    nota.setVolverMirar(ui->ckVolverMirar->checkState());
    nota.setNota(ui->txtNota->toPlainText());

    return nota;
}
