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

    QString nombre = casa->getNombre();
    int lugar = casa->getLugar();
    bool buscado = casa->getBuscado();
    bool wiki = casa->getWiki();
    // este  sería interesante hacerlo con QJson...
    //QString otrosnombres;
    QString notas = casa->getNotas();
    bool studiumgenerale = casa->getStudiumgenerale();

    query.prepare("INSERT INTO casas(nombre, lugar, buscado, wikipedia, studiumgenerale, notas) "
                  "VALUES(:nombre, :lugar, :buscado, :wiki, :studiumgenerale, :notas)");
    query.bindValue(":nombre", nombre);
    query.bindValue(":lugar", lugar);
    query.bindValue(":buscado", buscado);
    query.bindValue(":wiki", wiki);
    query.bindValue(":studiumgeneral", studiumgenerale);
    query.bindValue(":notas", notas);
    query.exec();

    this->select();
}
