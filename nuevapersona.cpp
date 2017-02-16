#include "nuevapersona.h"
#include "ui_nuevapersona.h"

#include <QDebug>

#include "persona.h"
#include "personasmodel.h"

NuevaPersona::NuevaPersona(PersonasModel *personas, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevaPersona), m_personas(personas)
{
    ui->setupUi(this);

    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarPersona()));

}

NuevaPersona::~NuevaPersona()
{
    delete ui;
}

void NuevaPersona::aceptarPersona(){

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
    persona->setNotas(notas);

    m_personas->AnadirPersona(persona);

}
