#include "personas.h"

#include <QSqlQuery>

#include "persona.h"

Personas::Personas(QObject *parent) :
    QSqlTableModel(parent)
{
    this->setTable("personas");

}

void Personas::AnadirPersona(const Persona *persona){
    QSqlQuery query;

    QString nombre = persona->getNombre();
    QString apellidos = persona->getApellidos();
    bool buscado = persona->getBuscado();
    bool wiki = persona->getWiki();
    bool viaf = persona->getViaf();
    QString wikilink = persona->getWikilink();
    QString viaflink = persona->getViaflink();
    QString notas = persona->getNotas();
    QString nacimiento = persona->getNacimiento();
    QString muerte = persona->getMuerte();
    // falta lo de los dos json

    query.prepare("INSERT INTO personas(nombre, apellidos, buscado, wikipedia, viaf, "
		  "wikipedia_link, viaf_link, nacimiento, muerte, notas) "
		  "VALUES (:nombre, :apellidos, :buscado, :wikipedia, :viaf, "
		  ":wikipedia_link, :viaf_link, :nacimiento, :muerte, :notas)");
    query.bindValue(":nombre", nombre);
    query.bindValue(":apellidos", apellidos);
    query.bindValue(":buscado", buscado);
    query.bindValue(":wikipedia", wiki);
    query.bindValue(":viaf", viaf);
    query.bindValue(":wikipedia_link", wikilink);
    query.bindValue(":viaf_link", viaflink);
    query.bindValue(":nacimiento", nacimiento);
    query.bindValue(":muerte", muerte);
    query.bindValue(":notas", notas);

    query.exec();

}
