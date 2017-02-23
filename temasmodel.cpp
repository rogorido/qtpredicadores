#include "temasmodel.h"

#include <QSqlQuery>

TemasModel *TemasModel::pInstance = 0;

TemasModel::TemasModel() :
    QSqlTableModel()
{
    this->setTable("temas");
}

TemasModel *TemasModel::InstanceModel(){
    if (pInstance == 0){
        pInstance = new TemasModel();
        atexit(&DestroyMe);
    }

    return pInstance;
}

void TemasModel::DestroyMe(){
    if (pInstance != NULL) delete pInstance;
}


void TemasModel::AnadirTema(const QString &tema){
    QSqlQuery query;

    query.prepare("INSERT INTO temas(tema) VALUES(:tema)");
    query.bindValue(":tema", tema);
    query.exec();

    this->select();
}