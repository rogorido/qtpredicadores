#include "temasmodel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

TemasModel *TemasModel::pInstance = 0;

TemasModel::TemasModel() :
    QSqlTableModel()
{
    this->setTable("themes");
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


bool TemasModel::AnadirTema(const Tema *tema){
    QSqlQuery query;

    QString tematitulo = tema->getTema();

    query.prepare("INSERT INTO themes(theme) VALUES(:tema)");
    query.bindValue(":tema", tematitulo);

    if (!query.exec()){
        qDebug() << query.lastError();
        return false;
    }
    else {
        this->select();
        emit(actualizado());
        return true;
    }

}
