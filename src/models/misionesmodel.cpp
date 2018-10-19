#include "misionesmodel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QDebug>

#include "objs/mision.h"

MisionesModel *MisionesModel::pInstance = 0;

MisionesModel::MisionesModel() :
    QSqlTableModel()
{
    this->setTable("filipinas.missions");
    this->select();
}

MisionesModel *MisionesModel::InstanceModel(){
    if (pInstance == 0){
        pInstance = new MisionesModel();
        atexit(&DestroyMe);
    }

    return pInstance;
}

void MisionesModel::DestroyMe(){
    if (pInstance != NULL) delete pInstance;
}

bool MisionesModel::AnadirMision(const Mision *mision){
    QSqlQuery query;
    QJsonDocument json;
    QString notas_json;

    int numero_mision = mision->getNumeroMision();
    int lugar_salida = mision->getLugarSalida();
    QDate fecha_salida = mision->getFechaSalida();
    QDate fecha_llegada = mision->getFechaLlegada();
    QString etapas = mision->getEtapasJson();
    Notas nota = mision->getNota();
    // tiene que haber una forma más fácil de hacer esto...
    // de hecho debería estar en lo propio de notas...
    QJsonObject nota_json = nota.getNotasJson();

    json = QJsonDocument(nota_json);
    notas_json = json.toJson(QJsonDocument::Compact);

    query.prepare("INSERT INTO filipinas.missions(mission_number, begin_date, arrival_date, "
                  "place_departure, stages, notes) "
                  "VALUES(:numero, :fechainicio, :fechafinal, "
                  ":lugar, :etapas, :notas)");
    query.bindValue(":numero", numero_mision);
    if (!lugar_salida == 0)
        query.bindValue(":lugar", lugar_salida);
    else
        query.bindValue(":lugar", QVariant(QVariant::Int));
    query.bindValue(":fechainicio", fecha_salida);
    query.bindValue(":fechafinal", fecha_llegada);
    query.bindValue(":etapas", etapas);
    if (notas_json != "{}")
        query.bindValue(":notas", notas_json);
    else
        query.bindValue(":notas", QVariant(QVariant::String));


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
