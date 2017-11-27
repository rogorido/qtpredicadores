#include "diocesismodel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#include "objs/diocesis.h"
#include "objs/notas.h"

DiocesisModel *DiocesisModel::pInstance = 0;

DiocesisModel::DiocesisModel() :
    QSqlTableModel()
{
    this->setTable("general.dioceses");
    this->select();

}

DiocesisModel *DiocesisModel::InstanceModel(){
    if (pInstance == 0){
        pInstance = new DiocesisModel();
        atexit(&DestroyMe);
    }

    return pInstance;
}

bool DiocesisModel::AnadirDiocesis(const Diocesis *diocesis)
{
    QSqlQuery query;
    QJsonDocument json;
    QString datos_json;

    QString nombre = diocesis->getNombre();
    QString nombre_latin = diocesis->getNombreLatin();
    int lugar = diocesis->getLugar();
    bool existe = diocesis->getExisteHoy();
    bool archidiocesis = diocesis->getArchidiocesis();
    int sufraganea = diocesis->getSufraganea();
    bool infidelibus = diocesis->getInfidelibus();
    bool titular_see = diocesis->getTitularSee();
    bool all_bishops = diocesis->getBuscadosTodosObispos();
    bool santa_sede = diocesis->getSantaSede();
    QString motivo_desaparicion = diocesis->getMotivoDesaparicion();
    QJsonObject otros_datos = diocesis->getOtrosDatos();
    Notas nota = diocesis->getNota();
    QJsonObject nota_json = nota.getNotasJson();

    /*
     * NOTE: joder no sé unir dos QJsonObjects. Es que
     * parece que no hay forma con los métodos existentes...
     * Hago esta pequeña chapuza, porque además no sé cómo gestionar
     * esto de si están llenos o no
     */
    if (!otros_datos.empty() && nota.estaLleno()){
        /*
         * si otros_datos no están vacios y nota está lleno
         * añadimos nota a otros_datos...
         */

        otros_datos.insert("nota", nota_json);
        json = QJsonDocument(otros_datos);
        datos_json = json.toJson(QJsonDocument::Compact);
    }
    else if (otros_datos.empty() && nota.estaLleno()){
        QJsonObject json_temp;

        json_temp.insert("nota", nota_json);
        json = QJsonDocument(json_temp);
        datos_json = json.toJson(QJsonDocument::Compact);
    }
    else if (!otros_datos.empty() && !nota.estaLleno()){
        json = QJsonDocument(otros_datos);
        datos_json = json.toJson(QJsonDocument::Compact);
    }
    else
        datos_json = "{}";

    query.prepare("INSERT INTO general.dioceses(diocese_name, diocese_latin_name, archidiocese, sufragean_id,"
                  "infidelibus, titular_see, disappeared, place_id, nowadays, other_data, "
                  "check_allbishops, vatican) "
                  "VALUES(:nombre, :nombre_latin, :archidiocesis, :sufraganea,  "
                  ":infidelibus, :titular_see, :desaparecida, :lugar, :hoy, :otrosdatos, "
                  ":todos_obispos, :santasede)");
    query.bindValue(":nombre", nombre);
    query.bindValue(":nombre_latin", nombre_latin);
    query.bindValue(":archidiocesis", archidiocesis);
    if (sufraganea != 0)
        query.bindValue(":sufraganea", sufraganea);
    else
        query.bindValue(":sufraganea", QVariant(QVariant::Int));
    if (lugar != 0)
        query.bindValue(":lugar", lugar);
    else
        query.bindValue(":lugar", QVariant(QVariant::Int));
    query.bindValue(":infidelibus", infidelibus);
    query.bindValue(":titular_see", titular_see);
    query.bindValue(":desaparecida", motivo_desaparicion);
    query.bindValue(":hoy", existe);
    if (datos_json != "{}")
        query.bindValue(":otrosdatos", datos_json);
    else
        query.bindValue(":otrosdatos", QVariant(QVariant::String));
    query.bindValue(":todos_obispos", all_bishops);
    query.bindValue(":santasede", santa_sede);

    if (!query.exec()){
        qDebug() << query.lastError();
        qDebug() << "esta es la query: " << query.executedQuery().toUtf8();
        return false;
    }
    else {
        this->select();
        emit(actualizado());
        return true;
    }

}

Diocesis *DiocesisModel::devolverDiocesis(int id)
{
    QSqlQuery query;
    Diocesis *diocesis = new Diocesis();
    QString json_otros;
    QJsonDocument json_doc;

    query.prepare("SELECT * FROM dioceses WHERE diocese_id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << query.lastError();
        qDebug() << "esta es la query: " << query.executedQuery().toUtf8();
        return diocesis;
    }

    query.first();

    diocesis->setId(id);
    diocesis->setNombre(query.value(1).toString());
    diocesis->setNombreLatin(query.value(2).toString());
    diocesis->setArchidiosis(query.value(3).toBool());
    diocesis->setSufraganea(query.value(4).toInt());
    diocesis->setExistente(query.value(5).toBool());
    diocesis->setLugar(query.value(6).toInt());
    diocesis->setInfidelibus(query.value(10).toBool());
    diocesis->setMotivoDesaparicion(query.value(11).toString());
    diocesis->setTitularSee(query.value(12).toBool());
    diocesis->setBuscadosTodosObispos(query.value(13).toBool());
    diocesis->setSantaSede(query.value(14).toBool());

    /*
     * pasamos lo de other_data con un sistema un poco embarullado
     * realmente ahí tb está lo de las notas...
     */
    json_otros = query.value(7).toString();
    json_doc = QJsonDocument::fromJson(json_otros.toUtf8());
    diocesis->setOtrosDatos(json_doc.object());

    return diocesis;
}

void DiocesisModel::actualizarDiocesis(int id)
{

}

void DiocesisModel::DestroyMe(){
    if (pInstance != NULL) delete pInstance;
}

