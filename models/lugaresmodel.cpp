#include "lugaresmodel.h"

#include <QSqlQuery>
#include <QDebug>

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

    query.prepare("INSERT INTO general.lugares(lugar, pais) VALUES(:lugar, :pais)");
    query.bindValue(":lugar", lugar);
    query.bindValue(":pais", pais);
    query.exec();

    this->select();
}

void LugaresModel::AnadirLugar(const QString &lugar, const QString &pais, const QString &otrosnombres){

    QSqlQuery query;

    query.prepare("INSERT INTO general.lugares(lugar, pais, otrosnombres) VALUES(:lugar, :pais, :otrosnombres)");
    query.bindValue(":lugar", lugar);
    query.bindValue(":pais", pais);
    query.bindValue(":otrosnombres", otrosnombres);
    query.exec();

    this->select();
}
