#include "casasmodel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "objs/casa.h"

CasasModel *CasasModel::pInstance = 0;

CasasModel::CasasModel() :
    QSqlTableModel()
{
    this->setTable("houses");

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

bool CasasModel::AnadirCasa(const Casa *casa){
    QSqlQuery query;

    QString nombre = casa->getNombre();
    QString nombre_latin = casa->getNombreLatin();
    int lugar = casa->getLugar();
    QString lugar_originario = casa->getLugarOriginario();
    bool masculino = casa->getMasculino();
    QString tipo = casa->getTipo();
    QString congregacion = casa->getCongregacion();
    bool buscado = casa->getBuscado();
    bool wiki = casa->getWiki();
    int provincia = casa->getProvincia();
    QString diocesis = casa->getDiocesis();
    QString fecha_fundacion = casa->getFechaFundacion();
    QString advocacion = casa->getAdvocacion();
    bool quetif = casa->getQuetif();
    // este  sería interesante hacerlo con QJson...
    //QString otrosnombres;
    QString notas = casa->getNotas();
    bool studiumgenerale = casa->getStudiumgenerale();

    query.prepare("INSERT INTO general.houses(name, latin_name, place_id, original_place, men, "
                  "type_house, congregation, lookedup, wikipedia, province_id, diocese, date_foundation, "
                  "quetif, advocation, studiumgenerale, notes) "
                  "VALUES(:nombre, :nombre_latin, :lugar, :lugaroriginario, :masculino, "
                  ":tipo, :congregacion, :buscado, :wiki, :provincia_id, :diocesis, :fecha_fundacion, "
                  ":quetif, :advocacion, :studiumgenerale, :notas)");
    query.bindValue(":nombre", nombre);
    query.bindValue(":nombre_latin", nombre_latin);
    if (!lugar == 0)
        query.bindValue(":lugar", lugar);
    else
        query.bindValue(":lugar", QVariant(QVariant::Int));
    query.bindValue(":lugaroriginario", lugar_originario);
    query.bindValue(":masculino", masculino);
    query.bindValue(":tipo", tipo);
    query.bindValue(":congregacion", congregacion);
    query.bindValue(":buscado", buscado);
    query.bindValue(":wiki", wiki);
    if (!provincia == 0)
        query.bindValue(":provincia_id", provincia);
    else
        query.bindValue(":provincia_id", QVariant(QVariant::Int));
    query.bindValue(":diocesis", diocesis);
    query.bindValue(":fecha_fundacion", fecha_fundacion);
    query.bindValue(":quetif", quetif);
    query.bindValue(":advocacion", advocacion);
    query.bindValue(":studiumgeneral", studiumgenerale);
    query.bindValue(":notas", notas);

    if (!query.exec()){
        qDebug() << query.lastError();
        qDebug() << "esta es la query: " << query.executedQuery().toUtf8();

        return false;
    }
    else {
        this->select();
        emit(actualizado());
        return true;
    }
}
