#include "personasmodel.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

#include "objs/persona.h"

PersonasModel *PersonasModel::pInstance = 0;

PersonasModel::PersonasModel() :
    QSqlTableModel()
{
    this->setTable("persons");
    this->select();

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

bool PersonasModel::AnadirPersona(const Persona *persona){
    QSqlQuery query;

    QString nombre = persona->getNombre();
    QString apellidos = persona->getApellidos();
    QString origen = persona->getOrigen();
    bool masculino = persona->getMasculino();
    bool buscado = persona->getBuscado();
    bool wiki = persona->getWiki();
    bool viaf = persona->getViaf();
    QString tipo_persona = persona->getTipoPersona();
    QString wikilink = persona->getWikilink();
    QString viaflink = persona->getViaflink();
    QString wikidata = persona->getWikidata();
    QString notas = persona->getNotas();
    QString nacimiento = persona->getNacimiento();
    QString muerte = persona->getMuerte();
    QString diocesis = persona->getDiocesis();
    bool volveramirar = persona->getVolverMirar();
    int cantidadinfo = persona->getCantidadInfo();
    QString otrosnombres = persona->getOtrosNombres();

    /*
     * cuando otrosnombres está vacío postgresql no permite
     * en un campo jsonb meter una cadena así vacía.
     * Hay que transformarla.
     */
    if (otrosnombres.isEmpty())
        otrosnombres = "{}";

    query.prepare("INSERT INTO general.persons(name, family_name, origin_name, lookedup, male, wikipedia, viaf, "
                  "other_names, wikipedia_link, viaf_link, wikidata_link, type_person, datebirth, "
                  "datedeath, birth_diocesis, look_again, quantity_info, notes) "
                  "VALUES (:nombre, :apellidos, :origen, :buscado, :masculino, :wikipedia, :viaf, "
                  ":otrosnombres, :wikipedia_link, :viaf_link, :wikidata_link, :tipo_persona, :nacimiento, "
                  ":muerte, :diocesis, :volveramirar, :cantidad_info, :notas)");
    query.bindValue(":nombre", nombre);
    query.bindValue(":apellidos", apellidos);
    query.bindValue(":origen", origen);
    query.bindValue(":buscado", buscado);
    query.bindValue(":masculino", masculino);
    query.bindValue(":wikipedia", wiki);
    query.bindValue(":viaf", viaf);
    query.bindValue(":otrosnombres", otrosnombres);
    query.bindValue(":wikipedia_link", wikilink);
    query.bindValue(":viaf_link", viaflink);
    query.bindValue(":wikidata_link", wikidata);
    query.bindValue(":tipo_persona", tipo_persona);
    query.bindValue(":nacimiento", nacimiento);
    query.bindValue(":diocesis", diocesis);
    query.bindValue(":muerte", muerte);
    query.bindValue(":volveramirar", volveramirar);
    query.bindValue(":cantidad_info", cantidadinfo);
    query.bindValue(":notas", notas);

    if (!query.exec()){
        qDebug() << query.lastError();
        return false;
    }
    else{
        this->select();
        emit(actualizado());
        return true;
    }

}

Persona *PersonasModel::devolverPersona(int id)
{

}
