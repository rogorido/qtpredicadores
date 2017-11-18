#include "dlgnuevolugar.h"
#include "ui_dlgnuevolugar.h"

#include <QSqlQueryModel>
#include <QCompleter>
#include <QMdiSubWindow>
#include <QDebug>
#include <QMessageBox>

#include "dlgdetalles.h"
#include "objs/lugar.h"
#include "objs/variados.h"
#include "models/lugaresmodel.h"
#include "models/qjsonmodel.h"
#include "widgets/myqmdiarea.h"

dlgNuevoLugar::dlgNuevoLugar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgNuevoLugar)
{
    ui->setupUi(this);

    mdiarea = MyQmdiArea::Instance(this);

    m_lugares = LugaresModel::InstanceModel();
    otrosnombres = new QJsonModel(this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->btOtrosNombres, SIGNAL(clicked(bool)), this, SLOT(anadirDetalles()));

    cargarModelos();
    ui->txtLugar->setFocus();
}

dlgNuevoLugar::~dlgNuevoLugar()
{
    delete ui;
}

void dlgNuevoLugar::anadirDetalles()
{
    dlgdetalles = new dlgDetalles(otrosnombres, OTROS, false, this);

    QMdiSubWindow *window = mdiarea->addSubWindow(dlgdetalles);
    window->show();
}

void dlgNuevoLugar::aceptar(){

    Lugar *lugar = new Lugar();

    QString nombre = ui->txtLugar->text();
    QString lugar_latin = ui->txtLugarLatin->text();
    QString pais = ui->txtPais->text();
    QString wikidata = ui->txtWikidata->text();
    QString tipo_lugar = ui->txtTipoLugar->text();
    QString nombres;

    lugar->setLugar(nombre);
    lugar->setLugarLatin(lugar_latin);
    lugar->setPais(pais);
    lugar->setWikidata(wikidata);
    lugar->setTipoLugar(tipo_lugar);

    if (otrosnombres->getSize() > 0)
        // entiendo q solo puede haber un elemento en la Qlist...
        nombres = otrosnombres->getJsonString(0);
    else
        nombres = "{}";

    lugar->setOtrosNombres(nombres);

    if (m_lugares->AnadirLugar(lugar)) {
        // borrarCampos(); realmente no tiene ahora mucho sentido...
        cerrar();
    }
    else {
        int ret = QMessageBox::warning(this, "Error al introducir el lugar",
                                       "Error al introducir el lugar en la BD");
        Q_UNUSED(ret)
        return;
    }

}

void dlgNuevoLugar::cerrar()
{
    parentWidget()->close();
}

void dlgNuevoLugar::cargarModelos(){

    m_paises = new QSqlQueryModel(this);
    m_paises_completer = new QCompleter(this);

    m_paises->setQuery("SELECT DISTINCT country FROM places ORDER BY country");

    m_paises_completer->setModel(m_paises);
    m_paises_completer->setCompletionColumn(0);
    ui->txtPais->setCompleter(m_paises_completer);

    QStringList tipos_lugar;
    tipos_lugar << "City" << "Province" << "Ruins";
    m_tipos_completer = new QCompleter(tipos_lugar, this);
    ui->txtTipoLugar->setCompleter(m_tipos_completer);

}

void dlgNuevoLugar::borrarCampos(){

    ui->txtLugar->setText("");
    ui->txtPais->setText("");
    ui->txtWikidata->setText("");
    ui->txtLugarLatin->setText("");

}
