#include "nuevacasa.h"
#include "ui_nuevacasa.h"

#include <QSqlRecord>
#include <QInputDialog>

#include "lugaresmodel.h"
#include "casa.h"
#include "casasmodel.h"

NuevaCasa::NuevaCasa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevaCasa)
{
    ui->setupUi(this);

    m_lugares = LugaresModel::InstanceModel();
    m_casas = CasasModel::InstanceModel();

    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarCasa()));
    connect(ui->btAnadirLugar, SIGNAL(clicked()), this, SLOT(anadirLugar()));

    ui->cboLugares->setModel(m_lugares);
    ui->cboLugares->setCurrentIndex(-1);
    ui->cboLugares->setModelColumn(1);

}

NuevaCasa::~NuevaCasa()
{
    delete ui;
}

void NuevaCasa::aceptarCasa(){

    Casa *casa = new Casa();

    QString nombre = ui->txtNombre->text();
    int lugar;
    bool buscado = ui->ckBuscado->checkState();
    bool wiki = ui->ckWiki->checkState();
    // este  sería interesante hacerlo con QJson...
    //QString otrosnombres;
    QString notas = ui->txtNotas->toPlainText();
    bool studiumgenerale = ui->ckStudium->checkState();

    QSqlRecord record = m_lugares->record(ui->cboLugares->currentIndex());
    lugar = record.value(0).toInt();

    casa->setNombre(nombre);
    casa->setLugar(lugar);
    casa->setBuscado(buscado);
    casa->setWiki(wiki);
    casa->setNotas(notas);
    casa->setStudiumgenerale(studiumgenerale);

    m_casas->AnadirCasa(casa);
}

void NuevaCasa::anadirLugar(){

    QString lugar;

    lugar = QInputDialog::getText(this, "Introduzca un nuevo lugar", "Lugar (nombre,país) ");

    if (!lugar.isEmpty()){
        m_lugares->AnadirLugar(lugar);
    }

}
