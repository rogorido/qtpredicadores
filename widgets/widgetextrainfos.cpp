#include "widgetextrainfos.h"
#include "ui_widgetextrainfos.h"

WidgetExtraInfos::WidgetExtraInfos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetExtraInfos)
{
    ui->setupUi(this);

    ui->txtLlave->setFocus();

    connect(ui->txtValor, SIGNAL(returnPressed()), this, SLOT(anadirPar()));
}

WidgetExtraInfos::~WidgetExtraInfos()
{
    delete ui;
}

void WidgetExtraInfos::anadirPar(){

    if (!ui->txtLlave->text().isEmpty() && !ui->txtValor->text().isEmpty()) {
        QPair<QString, QString> nuevo;
        nuevo.first = ui->txtLlave->text();
        nuevo.second = ui->txtValor->text();

        extras.append(nuevo);

        QString nuevoitem = nuevo.first + ': ' + nuevo.second;
        QListWidgetItem *item = new QListWidgetItem(nuevoitem, ui->lwExtraInfos);
    }
}

void WidgetExtraInfos::eliminarPar()
{

}
