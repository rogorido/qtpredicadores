#include "misionesmodel.h"

#include <QSqlQuery>
#include <QSqlError>
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

    int numero_mision = mision->getNumeroMision();
    int lugar_salida = mision->getLugarSalida();
    QDate fecha_salida = mision->getFechaSalida();
    QDate fecha_llegada = mision->getFechaLlegada();
    QString etapas = mision->getEtapasJson();

    query.prepare("INSERT INTO filipinas.missions(mission_number, begin_date, arrival_date, "
                  "place_departure, stages) "
                  "VALUES(:numero, :fechainicio, :fechafinal, "
                  ":lugar, :etapas)");
    query.bindValue(":numero", numero_mision);
    if (!lugar_salida == 0)
        query.bindValue(":lugar", lugar_salida);
    else
        query.bindValue(":lugar", QVariant(QVariant::Int));
    query.bindValue(":fechainicio", fecha_salida);
    query.bindValue(":fechafinal", fecha_llegada);
    query.bindValue(":etapas", etapas);

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
