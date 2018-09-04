#include "casasmodel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "objs/casa.h"

CasasModel *CasasModel::pInstance = 0;

CasasModel::CasasModel() :
    QSqlQueryModel()
{
    //this->setQuery("select * from houses");
    //this->select();

    /*
     *  estos iconos los defino aquí porque si los carga en el método data()
     * los está cargando cada vez que consulta ese método y va muy lento
     */
    icono_masculino = QIcon(":/icons/icons/masculino.png");
    icono_femenino = QIcon(":/icons/icons/femenino.png");

}

CasasModel *CasasModel::InstanceModel(){
    if (pInstance == 0){
        pInstance = new CasasModel();
        atexit(&DestroyMe);
    }

    return pInstance;
}

QVariant CasasModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QVariant value = QSqlQueryModel::data(index, role);

    if (role == Qt::DecorationRole && index.column() == 1) {
        QModelIndex i= index.model()->index(index.row(), 6);
        bool masculino = QSqlQueryModel::data(i, Qt::DisplayRole).toBool();
        if (masculino)
            return icono_masculino;
         else
            return icono_femenino;
    }

    return value;

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
    QString fecha_eliminacion = casa->getFechaEliminacion();
    QString advocacion = casa->getAdvocacion();
    bool quetif = casa->getQuetif();
    // este  sería interesante hacerlo con QJson...
    //QString otrosnombres;
    QString notas = casa->getNotas();
    QString otrosdatos = casa->getOtrosDatos();
    bool studiumgenerale = casa->getStudiumgenerale();

    query.prepare("INSERT INTO general.houses(name, latin_name, place_id, original_place, men, "
                  "type_house, congregation, lookedup, wikipedia, province_id, diocese, date_foundation, "
                  "date_elimination, quetif, advocation, studiumgenerale, notes, other_data) "
                  "VALUES(:nombre, :nombre_latin, :lugar, :lugaroriginario, :masculino, "
                  ":tipo, :congregacion, :buscado, :wiki, :provincia_id, :diocesis, :fecha_fundacion, "
                  ":fecha_eliminacion, :quetif, :advocacion, :studiumgenerale, :notas, :otrosdatos)");
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
    query.bindValue(":fecha_eliminacion", fecha_eliminacion);
    query.bindValue(":quetif", quetif);
    query.bindValue(":advocacion", advocacion);
    query.bindValue(":studiumgeneral", studiumgenerale);
    query.bindValue(":notas", notas);

    if (!otrosdatos.isEmpty())
        query.bindValue(":otrosdatos", otrosdatos);
    else
        query.bindValue(":otrosdatos", QVariant(QVariant::String));

    if (!query.exec()){
        qDebug() << query.lastError();
        qDebug() << "esta es la query: " << query.executedQuery().toUtf8();

        return false;
    }
    else {
        this->query().exec();
        emit(actualizado());
        return true;
    }
}
