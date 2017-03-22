#include "dlgnuevapersona.h"
#include "ui_dlgnuevapersona.h"

#include <QDebug>

#include "objs/persona.h"
#include "models/personasmodel.h"

dlgNuevaPersona::dlgNuevaPersona(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgNuevaPersona)
{
    ui->setupUi(this);

    m_personas = PersonasModel::InstanceModel();

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarPersona()));

}

dlgNuevaPersona::~dlgNuevaPersona()
{
    delete ui;
}

void dlgNuevaPersona::aceptarPersona(){

    Persona *persona = new Persona();

    QString nombre = ui->txtNombre->text();
    QString apellidos = ui->txtApellidos->text();
    bool buscado = ui->ckBuscado->checkState();
    bool wiki = ui->ckWiki->checkState();
    bool viaf = ui->ckViaf->checkState();
    QString wikilink = ui->txtWiki->text();
    QString viaflink = ui->txtViaf->text();
    QString notas = ui->txtNotas->toPlainText();
    QString nacimiento = ui->txtNacimiento->text();
    QString muerte = ui->txtMuerte->text();
    bool volveramirar = ui->ckVolverMirar->checkState();
    int cantidadinfo = ui->spCantidadInfo->value();
    // falta lo de los dos json

    persona->setNombre(nombre);
    persona->setApellidos(apellidos);
    persona->setBuscado(buscado);
    persona->setWiki(wiki);
    persona->setViaf(viaf);
    persona->setWikilink(wikilink);
    persona->setViaflink(viaflink);
    persona->setNacimiento(nacimiento);
    persona->setMuerte(muerte);
    persona->setVolverMirar(volveramirar);
    persona->setCantidadInfo(cantidadinfo);
    persona->setNotas(notas);

    m_personas->AnadirPersona(persona);

}
