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

Notas WidgetNotas::getNotas()
{
    nota.setVolverMirar(ui->ckVolverMirar->checkState());
    nota.setNota(ui->txtNota->toPlainText());

    return nota;
}

void WidgetNotas::on_txtNota_textChanged()
{
    emit(textoIntroducido());
}
