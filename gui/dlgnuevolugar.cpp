#include "dlgnuevolugar.h"
#include "ui_dlgnuevolugar.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QDebug>
#include <QMessageBox>

#include "objs/jsongestor.h"
#include "objs/lugar.h"
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

    Lugar *lugar = new Lugar();

    QString nombre = ui->txtLugar->text();
    QString lugar_latin = ui->txtLugarLatin->text();
    QString pais = ui->txtPais->text();
    QString wikidata = ui->txtWikidata->text();
    QString nombres;

    lugar->setLugar(nombre);
    lugar->setLugarLatin(lugar_latin);
    lugar->setPais(pais);
    lugar->setWikidata(wikidata);

    otrosnombres->actualizarPrevioIntroducir();

    if (otrosnombres->getSize() > 0)
        // entiendo q solo puede haber un elemento en la Qlist...
        nombres = otrosnombres->getJsonString(0);
    else
        nombres = "";

    lugar->setOtrosNombres(nombres);

    if (m_lugares->AnadirLugar(lugar)) {
        // borrarCampos(); realmente no tiene ahora mucho sentido...
        close();
    }
    else {
        int ret = QMessageBox::warning(this, "Error al introducir la resolución",
                                       "Error al introducir la resolución en la BD");
        return;
    }

}

void dlgNuevoLugar::cargarModelos(){

    m_paises = new QSqlQueryModel(this);
    m_paises_completer = new QCompleter(this);

    m_paises->setQuery("SELECT DISTINCT country FROM places ORDER BY country");

    m_paises_completer->setModel(m_paises);
    m_paises_completer->setCompletionColumn(0);
    ui->txtPais->setCompleter(m_paises_completer);

}

void dlgNuevoLugar::borrarCampos(){

    ui->txtLugar->setText("");
    ui->txtPais->setText("");
    ui->txtWikidata->setText("");
    ui->txtLugarLatin->setText("");

}
