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

void LugaresModel::AnadirLugar(const QString &lugar, const QString &pais){

    QSqlQuery query;

    query.prepare("INSERT INTO lugares(lugar, pais) VALUES(:lugar, :pais)");
    query.bindValue(":lugar", lugar);
    query.bindValue(":pais", pais);
    query.exec();

    this->select();
}
