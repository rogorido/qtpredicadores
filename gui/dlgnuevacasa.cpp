#include "dlgnuevacasa.h"
#include "ui_dlgnuevacasa.h"

#include <QSqlRecord>
#include <QInputDialog>

#include "models/lugaresmodel.h"
#include "objs/casa.h"
#include "models/casasmodel.h"

dlgNuevaCasa::dlgNuevaCasa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaCasa)
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

dlgNuevaCasa::~dlgNuevaCasa()
{
    delete ui;
}

void dlgNuevaCasa::aceptarCasa(){

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

void dlgNuevaCasa::anadirLugar(){

    QString lugar;

    lugar = QInputDialog::getText(this, "Introduzca un nuevo lugar", "Lugar (nombre,país) ");

    if (!lugar.isEmpty()){
        m_lugares->AnadirLugar(lugar);
    }

}
