#include "casasmodel.h"

#include <QSqlQuery>

#include "objs/casa.h"

CasasModel *CasasModel::pInstance = 0;

CasasModel::CasasModel() :
    QSqlTableModel()
{
    this->setTable("casas");

}

CasasModel *CasasModel::InstanceModel(){
    if (pInstance == 0){
        pInstance = new CasasModel();
        atexit(&DestroyMe);
    }

    return pInstance;
}

void CasasModel::DestroyMe(){
    if (pInstance != NULL) delete pInstance;
}

void CasasModel::AnadirCasa(const Casa *casa){
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
