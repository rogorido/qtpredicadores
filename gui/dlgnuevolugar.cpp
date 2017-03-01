#include "dlgnuevolugar.h"
#include "ui_dlgnuevolugar.h"

#include <QSqlQueryModel>
#include <QCompleter>

#include "objs/jsongestor.h"
#include "models/lugaresmodel.h"

dlgNuevoLugar::dlgNuevoLugar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevoLugar)
{
    ui->setupUi(this);

    m_lugares = LugaresModel::InstanceModel();

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));

    cargarModelos();
}

dlgNuevoLugar::~dlgNuevoLugar()
{
    delete ui;
}

void dlgNuevoLugar::aceptar(){

}

void dlgNuevoLugar::cargarModelos(){

    m_paises = new QSqlQueryModel(this);
    m_paises_completer = new QCompleter(this);
    otrosnombres = new JsonGestor(this);

    m_paises->setQuery("SELECT DISTINCT pais FROM lugares ORDER BY pais");
    m_paises_completer->setModel(m_paises);

}
