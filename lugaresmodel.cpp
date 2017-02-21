#include "lugaresmodel.h"

#include <QSqlQuery>

LugaresModel * LugaresModel::pInstance = 0;

LugaresModel::LugaresModel() :
    QSqlTableModel()
{
    this->setTable("lugares");
}

LugaresModel *LugaresModel::InstanceModel(){

    if (pInstance == 0){
        pInstance = new LugaresModel();
        atexit(&DestroyMe);
    }

    return pInstance;
}

void LugaresModel::DestroyMe(){
    if (pInstance != NULL) delete pInstance;
}

void LugaresModel::AnadirLugar(const QString lugar){

    /*
     * TODO: habría que comprobar que siemrpe hay país...
     */
    QSqlQuery query;
    QStringList campos = lugar.split(',');

    query.prepare("INSERT INTO lugares(lugar, pais) VALUES(:lugar, :pais)");
    query.bindValue(":lugar", campos[0]);
    query.bindValue(":pais", campos[1]);
    query.exec();

    this->select();
}
