#include "nuevacasa.h"
#include "ui_nuevacasa.h"

#include <QSqlRecord>

#include "lugaresmodel.h"
#include "casa.h"
#include "casasmodel.h"

NuevaCasa::NuevaCasa(CasasModel *casas, LugaresModel *lugares, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevaCasa), m_lugares(lugares), m_casas(casas)
{
    ui->setupUi(this);

    connect(ui->btCancelar, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked()), this, SLOT(aceptarCasa()));

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
