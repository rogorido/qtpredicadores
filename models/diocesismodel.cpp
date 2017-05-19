#include "diocesismodel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

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
    QSqlQuery query;
    QJsonDocument json;
    QString otros_datos_string;

    QString nombre = diocesis->getNombre();
    QString nombre_latin = diocesis->getNombreLatin();
    int lugar = diocesis->getLugar();
    bool existe = diocesis->getExisteHoy();
    bool archidiocesis = diocesis->getArchidiocesis();
    int sufraganea = diocesis->getSufraganea();
    QJsonObject otros_datos = diocesis->getOtrosDatos();

    if (!otros_datos.empty()){
        json = QJsonDocument(otros_datos);
        otros_datos_string = json.toJson(QJsonDocument::Compact);
    }
    else
        otros_datos_string = "{}";

    query.prepare("INSERT INTO general.dioceses(diocese_name, diocese_latin_name, archidiocese, sufragean_id, "
                  "place_id, nowadays, other_data) "
                  "VALUES(:nombre, :nombre_latin, :archidiocesis, :sufraganea, :lugar, :hoy, :otrosdatos)");
    query.bindValue(":nombre", nombre);
    query.bindValue(":nombre_latin", nombre_latin);
    query.bindValue(":archidiocesis", archidiocesis);
    if (sufraganea != 0)
        query.bindValue(":sufraganea", sufraganea);
    else
        query.bindValue(":sufraganea", QVariant(QVariant::Int));
    if (lugar != 0)
        query.bindValue(":lugar", lugar);
    else
        query.bindValue(":lugar", QVariant(QVariant::Int));
    query.bindValue(":hoy", existe);
    query.bindValue(":otrosdatos", otros_datos_string);

    if (!query.exec()){
        qDebug() << query.lastError();
        qDebug() << "esta es la query: " << query.executedQuery().toUtf8();
        return false;
    }
    else {
        this->select();
        return true;
    }

}

void DiocesisModel::DestroyMe(){
    if (pInstance != NULL) delete pInstance;
}

