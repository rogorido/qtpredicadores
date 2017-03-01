#include "dlgnuevacasa.h"
#include "ui_dlgnuevacasa.h"

#include <QSqlRecord>
#include <QInputDialog>

#include "models/lugaresmodel.h"
#include "models/casasmodel.h"
#include "models/provinciasmodel.h"
#include "objs/casa.h"
#include "gui/dlgseleccionarlugar.h"

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
    connect(ui->btQuitarLugar, SIGNAL(clicked()), this, SLOT(quitarLugar()));

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

    // TODO: hay que comprobar que esté vacío?
    lugar = lugar_struct.id;

    casa->setNombre(nombre);
    casa->setLugar(lugar);
    casa->setBuscado(buscado);
    casa->setWiki(wiki);
    casa->setNotas(notas);
    casa->setStudiumgenerale(studiumgenerale);

    m_casas->AnadirCasa(casa);
}

void dlgNuevaCasa::anadirLugar(){

    dlgSeleccionarLugar *dlgLugar = new dlgSeleccionarLugar(this);
    dlgLugar->show();

    connect(dlgLugar, SIGNAL(lugarEscogido(Lugar)), this, SLOT(recibirLugar(Lugar)));

}

void dlgNuevaCasa::recibirLugar(Lugar lugarescogido){

    lugar_struct.id = lugarescogido.getId();
    lugar_struct.elemento = lugarescogido.getLugar();

    ui->txtLugar->setText(lugar_struct.elemento);

}

void dlgNuevaCasa::quitarLugar(){

    lugar_struct = elementopareado();
}
