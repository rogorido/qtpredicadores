#include "dlgnuevolugar.h"
#include "ui_dlgnuevolugar.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QDebug>

#include "objs/jsongestor.h"
#include "models/lugaresmodel.h"
#include "dlgdetalles.h"

dlgNuevoLugar::dlgNuevoLugar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevoLugar)
{
    ui->setupUi(this);

    m_lugares = LugaresModel::InstanceModel();
    otrosnombres = new JsonGestor(this);

    dlgdetalles = new dlgDetalles(otrosnombres, this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->btOtrosNombres, SIGNAL(clicked(bool)), dlgdetalles, SLOT(show()));

    cargarModelos();
}

dlgNuevoLugar::~dlgNuevoLugar()
{
    delete ui;
}

void dlgNuevoLugar::aceptar(){

    QString lugar;
    QString pais;
    QString nombres;

    lugar = ui->txtLugar->text();
    pais = ui->txtPais->text();

    otrosnombres->actualizarPrevioIntroducir();

    if (otrosnombres->getSize() > 0)
        // entiendo q solo puede haber un elemento en la Qlist...
        nombres = otrosnombres->getJsonString(0);

    if (nombres.isEmpty()){
        qDebug() << "estamos aqui...";
        m_lugares->AnadirLugar(lugar, pais);}
    else
        m_lugares->AnadirLugar(lugar, pais, nombres);

    close();

}

void dlgNuevoLugar::cargarModelos(){

    m_paises = new QSqlQueryModel(this);
    m_paises_completer = new QCompleter(this);

    m_paises->setQuery("SELECT DISTINCT pais FROM lugares ORDER BY pais");

    m_paises_completer->setModel(m_paises);
    m_paises_completer->setCompletionColumn(0);
    ui->txtPais->setCompleter(m_paises_completer);

}
