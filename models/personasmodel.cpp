#include "personasmodel.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

#include "objs/persona.h"
#include "models/qjsonmodel.h"

PersonasModel *PersonasModel::pInstance = 0;

PersonasModel::PersonasModel() :
    QSqlQueryModel()
{
    // cargamos la query...
    cargarQueryInicial();

    /*
     *  estos iconos los defino aquí porque si los carga en el método data()
     * los está cargando cada vez que consulta ese método y va muy lento
     */
    icono_masculino = QIcon(":/icons/icons/masculino.png");
    icono_femenino = QIcon(":/icons/icons/femenino.png");

}

PersonasModel *PersonasModel::InstanceModel()
{

    if (pInstance == 0){
        pInstance = new PersonasModel();
        atexit(&DestroyMe);
    }

    return pInstance;
}

QVariant PersonasModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QVariant value = QSqlQueryModel::data(index, role);

    if (role == Qt::DecorationRole && index.column() == 1) {
        QModelIndex i= index.model()->index(index.row(), 4);
        bool masculino = QSqlQueryModel::data(i, Qt::DisplayRole).toBool();
        if (masculino)
            return icono_masculino;
         else
            return icono_femenino;
    }

    return value;

}

void PersonasModel::DestroyMe()
{
    if (pInstance != NULL) delete pInstance;
}

void PersonasModel::cargarQueryInicial()
{
    this->setQuery("SELECT * FROM vistas.persons_alternatives");
}

bool PersonasModel::AnadirPersona(const Persona *persona, int persona_id)
{
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

    if (persona_id == 0) {
        query.prepare("INSERT INTO general.persons(name, family_name, origin_name, lookedup, male, wikipedia, viaf, "
                      "other_names, wikipedia_link, viaf_link, wikidata_link, type_person, datebirth, "
                      "datedeath, birth_diocesis, look_again, quantity_info, notes) "
                      "VALUES (:nombre, :apellidos, :origen, :buscado, :masculino, :wikipedia, :viaf, "
                      ":otrosnombres, :wikipedia_link, :viaf_link, :wikidata_link, :tipo_persona, :nacimiento, "
                      ":muerte, :diocesis, :volveramirar, :cantidad_info, :notas)");
    }
    else {
        query.prepare("UPDATE general.persons SET (name, family_name, origin_name, lookedup, male, wikipedia, viaf, "
                      "other_names, wikipedia_link, viaf_link, wikidata_link, type_person, datebirth, "
                      "datedeath, birth_diocesis, look_again, quantity_info, notes) "
                      "= (:nombre, :apellidos, :origen, :buscado, :masculino, :wikipedia, :viaf, "
                      ":otrosnombres, :wikipedia_link, :viaf_link, :wikidata_link, :tipo_persona, :nacimiento, "
                      ":muerte, :diocesis, :volveramirar, :cantidad_info, :notas) "
                      "WHERE person_id = :person_id");
    }

    // rellenamos los campos
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

    if (persona_id != 0)
        query.bindValue(":person_id", persona_id);

    if (!query.exec()){
        qDebug() << query.lastError();
        return false;
    }
    else{
        cargarQueryInicial();
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

    query.first();

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

QJsonModel *PersonasModel::devolverDetalles(int id)
{
    QSqlQuery query;
    QString sql;
    QJsonModel *json_model = new QJsonModel();
    QJsonDocument json;

    sql = QString("SELECT details FROM persons_details WHERE person_id=%1").arg(id);
    query.exec(sql);

    /*
     * joder, que lío hay que hacer para construir un json...
     * hay que usar eso de QByteArray pq con una QString normal
     * no hay manera...
     */
    while (query.next()) {
        QByteArray datos = query.value(0).toByteArray();
        json = QJsonDocument::fromJson(datos);
        /*
         * tenemos que pasar json.object que construye un
         * QjsonObject, que es al parecer tb un QJsonValue
         * y es lo que pide anadirJson...
         */
        json_model->anadirJson(json.object());
    }

    json_model->resetearModelo();

    return json_model;

}
