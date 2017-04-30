#include "dlgpenaentrada.h"
#include "ui_dlgpenaentrada.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QListWidgetItem>
#include <QModelIndex>

#include <QDebug>

dlgPenaEntrada::dlgPenaEntrada(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgPenaEntrada)
{
    ui->setupUi(this);

    //connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->btEliminarPenas, SIGNAL(clicked(bool)), this, SLOT(quitarPenasTipos()));
    connect(ui->btEliminarPenados, SIGNAL(clicked(bool)), this, SLOT(quitarPenados()));
    connect(ui->txtTipos, SIGNAL(returnPressed()), this, SLOT(anadirPenasTipos()));
    connect(ui->txtPenados, SIGNAL(returnPressed()), this, SLOT(anadirPenados()));

    cargarModelos();
}

dlgPenaEntrada::~dlgPenaEntrada()
{
    delete ui;
}

void dlgPenaEntrada::aceptar()
{
    pena.setPenasTipos(penastipos);
    pena.setDuracion(ui->txtDuracion->text());
    pena.setPenados(penados);
    pena.setSeguridad(ui->spSeguridad->value());
    pena.setMotivo(ui->txtMotivo->text());
    // TODO: falta penatexto!

    emit(aceptarPena(pena));

    close();
}

void dlgPenaEntrada::anadirPenasTipos()
{
    if (!ui->txtTipos->text().isEmpty()){
        qDebug() << "pulsado return...";
        penastipos.append(ui->txtTipos->text());
        QListWidgetItem *item = new QListWidgetItem(ui->txtTipos->text(), ui->lwTipos);
        ui->txtTipos->setText("");
    }
}

void dlgPenaEntrada::quitarPenasTipos()
{
    QModelIndex idx = ui->lwTipos->currentIndex();

    if (!idx.isValid())
        return;

    QString tipo = idx.data().toString();

    for (int i = 0; i < penastipos.size(); ++i) {
        if (penastipos.value(i) == tipo) {
            penastipos.removeAt(i);
            break;
        }
    }

    ui->lwTipos->takeItem(ui->lwTipos->currentRow());

}

void dlgPenaEntrada::anadirPenados()
{
    if (!ui->txtPenados->text().isEmpty()){
        penados.append(ui->txtPenados->text());
        QListWidgetItem *item = new QListWidgetItem(ui->txtPenados->text(), ui->lwPenados);
        ui->txtPenados->setText("");
    }
}

void dlgPenaEntrada::quitarPenados()
{
    QModelIndex idx = ui->lwPenados->currentIndex();

    if (!idx.isValid())
        return;

    QString penado = idx.data().toString();

    for (int i = 0; i < penados.size(); ++i) {
        if (penados.value(i) == penado) {
            penados.removeAt(i);
            break;
        }
    }

    ui->lwPenados->takeItem(ui->lwPenados->currentRow());


}

void dlgPenaEntrada::cargarModelos()
{

}
