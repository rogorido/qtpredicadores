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
    QSqlQuery query;
    Persona *persona = new Persona();

    query.prepare("SELECT * FROM persons WHERE person_id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << query.lastError();
        qDebug() << "esta es la query: " << query.executedQuery().toUtf8();
        return persona;
    }

    persona->setId(id);
    persona->setNombre(query.value(Persona::CamposPersona::NAME).toString());
    persona->setApellidos(query.value(Persona::CamposPersona::FAMILY_NAME).toString());
    // TODO: falta othernames pq es json!
    persona->setBuscado(query.value(Persona::CamposPersona::LOOKEDUP).toBool());
    persona->setWiki(query.value(Persona::CamposPersona::WIKIPEDIA).toBool());
    persona->setViaf(query.value(Persona::CamposPersona::VIAF).toBool());
    persona->setWikilink(query.value(Persona::CamposPersona::WIKIPEDIA_LINK).toString());
    persona->setViaflink(query.value(Persona::CamposPersona::VIAF_LINK).toString());
    persona->setWikidata(query.value(Persona::CamposPersona::WIKIDATA_LINK).toString());
    persona->setNacimiento(query.value(Persona::CamposPersona::DATEBIRTH).toString());
    persona->setMuerte(query.value(Persona::CamposPersona::DATEDEATH).toString());
    persona->setCantidadInfo(query.value(Persona::CamposPersona::QUANTITY_INFO).toInt());
    // TODO: Atención falta lo de interesting
    persona->setVolverMirar(query.value(Persona::CamposPersona::LOOK_AGAIN).toBool());
    persona->setNotas(query.value(Persona::CamposPersona::NOTES).toString());
    // TODO: falta other-data pq es jsonb
    persona->setOrigen(query.value(Persona::CamposPersona::ORIGIN_NAME).toString());
    persona->setDiocesis(query.value(Persona::CamposPersona::BIRTH_DIOCESIS).toString());
    persona->setMasculino(query.value(Persona::CamposPersona::MALE).toBool());
    persona->setTipoPersona(query.value(Persona::CamposPersona::TYPE_PERSON).toString());

    return persona;

}
