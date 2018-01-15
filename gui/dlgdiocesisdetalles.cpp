#include "dlgdiocesisdetalles.h"
#include "ui_dlgdiocesisdetalles.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QCompleter>
#include <QMdiSubWindow>

#include "widgets/myqmdiarea.h"

dlgDiocesisDetalles::dlgDiocesisDetalles(int diocesis_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgDiocesisDetalles),
    dioc_id(diocesis_id)
{
    ui->setupUi(this);

    mdiarea = MyQmdiArea::Instance(this);

    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(cancelar()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptar()));

    cargarModelos();
    ui->spTomo->setFocus();

}

dlgDiocesisDetalles::~dlgDiocesisDetalles()
{
    delete ui;
}

void dlgDiocesisDetalles::aceptar()
{
    QSqlQuery query;

    int tomo = ui->spTomo->value();
    int anoref = ui->spAnoRef->value();
    int rentas = ui->spRenta->value();
    int tasa = ui->spTaxa->value();
    QString senor = ui->txtSenorTemporal->text();
    int canonigos = ui->spCanonicos->value();
    int dignidades = ui->spDignidades->value();
    int beneficiados = ui->spBeneficiados->value();
    bool inmediata = ui->ckInmediata->checkState();
    bool sindatos = ui->ckSinDatos->checkState();


}

void dlgDiocesisDetalles::cancelar()
{
    parentWidget()->close();

}

void dlgDiocesisDetalles::cargarModelos()
{

}

void dlgDiocesisDetalles::borrarCampos()
{
    // dejamos el tomo, año como están porque seguramente meto varios

    ui->ckInmediata->setCheckState(Qt::Unchecked);
    ui->ckSinDatos->setCheckState(Qt::Unchecked);
    ui->spRenta->setValue(0);
    ui->spTaxa->setValue(0);
    ui->spCanonicos->setValue(0);
    ui->spDignidades->setValue(0);
    ui->spBeneficiados->setValue(0);
    ui->txtSenorTemporal->setText("");

    ui->wdExtras->clear();
    ui->wdNotas->reiniciar();

    ui->spTomo->setFocus();

}
