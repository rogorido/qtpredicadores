#include "personasmodel.h"

#include <QSqlQuery>

#include "objs/persona.h"

PersonasModel *PersonasModel::pInstance = 0;

PersonasModel::PersonasModel() :
    QSqlTableModel()
{
    this->setTable("personas");

}

PersonasModel *PersonasModel::InstanceModel(){

    if (pInstance == 0){
        pInstance = new PersonasModel();
        atexit(&DestroyMe);
    }

    return pInstance;
}

void PersonasModel::DestroyMe(){
    if (pInstance != NULL) delete pInstance;
}

void PersonasModel::AnadirPersona(const Persona *persona){
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
    bool volveramirar = persona->getVolverMirar();
    int cantidadinfo = persona->getCantidadInfo();
    // falta lo de los dos json

    query.prepare("INSERT INTO persons(name, family_name, lookedup, wikipedia, viaf, "
          "wikipedia_link, viaf_link, datebirth, datedeath, look_again, quantity_info, notes) "
		  "VALUES (:nombre, :apellidos, :buscado, :wikipedia, :viaf, "
          ":wikipedia_link, :viaf_link, :nacimiento, :muerte, :volveramirar, :cantidad_info, :notas)");
    query.bindValue(":nombre", nombre);
    query.bindValue(":apellidos", apellidos);
    query.bindValue(":buscado", buscado);
    query.bindValue(":wikipedia", wiki);
    query.bindValue(":viaf", viaf);
    query.bindValue(":wikipedia_link", wikilink);
    query.bindValue(":viaf_link", viaflink);
    query.bindValue(":nacimiento", nacimiento);
    query.bindValue(":muerte", muerte);
    query.bindValue(":volveramirar", volveramirar);
    query.bindValue(":cantidad_info", cantidadinfo);
    query.bindValue(":notas", notas);

    query.exec();

    this->select();
    emit(actualizado());

}
