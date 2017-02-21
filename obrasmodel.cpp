#include "obrasmodel.h"

#include <QSqlQuery>

#include "obra.h"

ObrasModel *ObrasModel::pInstance = 0;

ObrasModel::ObrasModel() :
    QSqlTableModel()
{
    this->setTable("obras");
}

ObrasModel *ObrasModel::InstanceModel(){
    if (pInstance == 0){
        pInstance = new ObrasModel();
        atexit(&DestroyMe);
    }

    return pInstance;
}

void ObrasModel::DestroyMe(){
    if (pInstance != NULL) delete pInstance;
}

void ObrasModel::AnadirObra(const Obra *obra){
    QSqlQuery query;

    this->select();
}
