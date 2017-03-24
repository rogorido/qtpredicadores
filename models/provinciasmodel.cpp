#include "provinciasmodel.h"

#include <QSqlQuery>

#include "objs/provincia.h"

ProvinciasModel *ProvinciasModel::pInstance = 0;

ProvinciasModel::ProvinciasModel() :
    QSqlTableModel()
{
    this->setTable("provinces");

}

ProvinciasModel *ProvinciasModel::InstanceModel(){
    if (pInstance == 0){
        pInstance = new ProvinciasModel();
        atexit(&DestroyMe);
    }

    return pInstance;
}

void ProvinciasModel::DestroyMe(){
    if (pInstance != NULL) delete pInstance;
}

void ProvinciasModel::AnadirProvincia(const Provincia *provincia){
    QSqlQuery query;

    QString nombre = provincia->getNombre();
    QString otros_nombres = provincia->getOtrosNombres();
    QString erigida = provincia->getErigida();
    QString notas = provincia->getNotas();

    query.prepare("INSERT INTO provinces(name, other_names, erected, notes) "
                  "VALUES(:nombre, :otrosnombres, :erigida, :notas)");
    query.bindValue(":nombre", nombre);
    query.bindValue(":otrosnombres", otros_nombres);
    query.bindValue(":erigida", erigida);
    query.bindValue(":notas", notas);
    query.exec();

    this->select();
    emit(actualizado());
}
