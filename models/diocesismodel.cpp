#include "diocesismodel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

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

    QString nombre = diocesis->getNombre();
    QString nombre_latin = diocesis->getNombreLatin();
    int lugar = diocesis->getLugar();
    bool existe = diocesis->getExisteHoy();
    bool archidiocesis = diocesis->getArchidiocesis();
    int sufraganea = diocesis->getSufraganea();

    query.prepare("INSERT INTO general.dioceses(diocese_name, diocese_latin_name, archidiocese, sufragean_id, "
                  "place_id, nowadays) "
                  "VALUES(:nombre, :nombre_latin, :archidiocesis, :sufraganea, :lugar, :hoy)");
    query.bindValue(":nombre", nombre);
    query.bindValue(":nombre_latin", nombre_latin);
    query.bindValue(":archidiocesis", archidiocesis);
    query.bindValue(":sufraganea", sufraganea);
    query.bindValue(":lugar", lugar);
    query.bindValue(":hoy", existe);

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

