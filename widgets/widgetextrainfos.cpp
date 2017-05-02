#include "widgetextrainfos.h"
#include "ui_widgetextrainfos.h"

WidgetExtraInfos::WidgetExtraInfos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetExtraInfos)
{
    ui->setupUi(this);

    ui->txtLlave->setFocus();

    connect(ui->txtValor, SIGNAL(returnPressed()), this, SLOT(anadirPar()));
    connect(ui->btEliminarExtraInfo, SIGNAL(clicked(bool)), this, SLOT(eliminarPar()));
}

WidgetExtraInfos::~WidgetExtraInfos()
{
    delete ui;
}

ExtraInfos WidgetExtraInfos::getExtraInfos()
{
    return extras;
}

void WidgetExtraInfos::clear()
{
    extras.clear();
    ui->lwExtraInfos->clear();
}

void WidgetExtraInfos::anadirPar(){

    if (!ui->txtLlave->text().isEmpty() && !ui->txtValor->text().isEmpty()) {
        QPair<QString, QString> nuevo;
        nuevo.first = ui->txtLlave->text();
        nuevo.second = ui->txtValor->text();

        extras.append(nuevo);

        QString nuevoitem = nuevo.first + ': ' + nuevo.second;
        QListWidgetItem *item = new QListWidgetItem(nuevoitem, ui->lwExtraInfos);

        ui->txtLlave->setText("");
        ui->txtValor->setText("");
        ui->txtLlave->setFocus();
    }
}

void WidgetExtraInfos::eliminarPar()
{
    QModelIndex idx = ui->lwExtraInfos->currentIndex();

    if (!idx.isValid())
        return;

    int identificador = idx.row();

    extras.removeAt(identificador);

    ui->lwExtraInfos->takeItem(ui->lwExtraInfos->currentRow());
}
