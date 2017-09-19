#include "widgetextrainfos.h"
#include "ui_widgetextrainfos.h"

#include <QSqlQueryModel>
#include <QCompleter>

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

void WidgetExtraInfos::recibirConsultasCompleter(QString sql_claves, QString sql_valores)
{
    librekeys_model = new QSqlQueryModel(this);
    librekeys_model->setQuery(sql_claves);

    librekeys_completer = new QCompleter(librekeys_model, this);
    librekeys_completer->setCompletionColumn(0);
    librekeys_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtLlave->setCompleter(librekeys_completer);

    librevalues_model = new QSqlQueryModel(this);
    librevalues_model->setQuery(sql_valores);

    librevalues_completer = new QCompleter(librevalues_model, this);
    librevalues_completer->setCompletionColumn(0);
    librevalues_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtValor->setCompleter(librevalues_completer);

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
