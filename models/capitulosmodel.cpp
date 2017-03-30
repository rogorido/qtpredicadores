#include "capitulosmodel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "objs/capitulo.h"

CapitulosModel *CapitulosModel::pInstance = 0;

CapitulosModel::CapitulosModel() :
    QSqlTableModel()
{
    this->setTable("chapters.chapters");

}

CapitulosModel *CapitulosModel::InstanceModel(){
    if (pInstance == 0){
        pInstance = new CapitulosModel();
        atexit(&DestroyMe);
    }

    return pInstance;
}

void CapitulosModel::DestroyMe(){
    if (pInstance != NULL) delete pInstance;
}

void CapitulosModel::AnadirCapitulo(const Capitulo *capitulo){
    QSqlQuery query;

    QString nombre = capitulo->getNombre();
    QString nombre_latin = capitulo->getNombreLatin();
    int lugar = capitulo->getLugar();
    QString lugar_originario = capitulo->getLugarOriginario();
    bool masculino = capitulo->getMasculino();
    QString tipo = capitulo->getTipo();
    QString congregacion = capitulo->getCongregacion();
    bool buscado = capitulo->getBuscado();
    bool wiki = capitulo->getWiki();
    int provincia = capitulo->getProvincia();
    QString diocesis = capitulo->getDiocesis();
    QString fecha_fundacion = capitulo->getFechaFundacion();
    QString advocacion = capitulo->getAdvocacion();
    // este  sería interesante hacerlo con QJson...
    //QString otrosnombres;
    QString notas = capitulo->getNotas();
    bool studiumgenerale = capitulo->getStudiumgenerale();

    query.prepare("INSERT INTO general.houses(name, latin_name, place_id, original_place, men, "
                  "type_house, congregation, lookedup, wikipedia, province_id, diocese, date_foundation, "
                  "advocation, studiumgenerale, notes) "
                  "VALUES(:nombre, :nombre_latin, :lugar, :lugaroriginario, :masculino, "
                  ":tipo, :congregacion, :buscado, :wiki, :provincia_id, :diocesis, :fecha_fundacion, "
                  ":advocacion, :studiumgenerale, :notas)");
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
    query.bindValue(":advocacion", advocacion);
    query.bindValue(":studiumgeneral", studiumgenerale);
    query.bindValue(":notas", notas);

    if (!query.exec()){
        qDebug() << query.lastError();
        qDebug() << "esta es la query: " << query.executedQuery().toUtf8();

        return;
    }

    this->select();
    emit(actualizado());
}
