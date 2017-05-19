#include "diocesismodel.h"

#include "objs/diocesis.h"

DiocesisModel *DiocesisModel::pInstance = 0;

DiocesisModel::DiocesisModel() :
    QSqlTableModel()
{
    this->setTable("general.diocesis");

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

}

void DiocesisModel::DestroyMe(){
    if (pInstance != NULL) delete pInstance;
}

