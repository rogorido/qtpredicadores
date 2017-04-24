#include "resolucionesmodel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "objs/resolucion.h"

ResolucionesModel *ResolucionesModel::pInstance = 0;

ResolucionesModel::ResolucionesModel() :
    QSqlTableModel()
{
    this->setTable("chapters.resolutions");

}

ResolucionesModel *ResolucionesModel::InstanceModel(){
    if (pInstance == 0){
        pInstance = new ResolucionesModel();
        atexit(&DestroyMe);
    }

    return pInstance;
}

void ResolucionesModel::DestroyMe(){
    if (pInstance != NULL) delete pInstance;
}

bool ResolucionesModel::anadirResolucion(const Resolucion *resolucion){
    QSqlQuery query;

    QString texto = resolucion->getTexto();
    QString texto_traducido = resolucion->getTextoTraducido();
    QString texto_resumido = resolucion->getTextoResumido();
    int capitulo = resolucion->getCapitulo();
    QString epigrafe = resolucion->getEpigrafe();
    int provincia = resolucion->getProvincia();
    bool entendido = resolucion->getEntendido();
    bool volveramirar = resolucion->getVolverMirar();
    bool traducido = resolucion->getTraducido();
    bool razonada = resolucion->getRazonada();
    int interesante = resolucion->getInteres();
    int resolucion_anterior = resolucion->getResolucionAnterior();
    QString notas = resolucion->getNotas();

    query.prepare("INSERT INTO chapters.resolutions(resolution_text, resolution_traduction, resolution_summary, chapter, "
          "small_title, understood, look_again, province_id, translated, motivated, interesting, resolution_previous, notes) "
          "VALUES(:resolucion_texto, :resolucion_traduccion, :resolucion_resumen, :capitulo, "
          ":epigrafe, :entendida, :volveramirar, :provincia, :traducida, :razonada, :interesante, :resolucion_anterior, :notas)");
    query.bindValue(":resolucion_texto", texto);
    query.bindValue(":resolucion_traduccion", texto_traducido);
    query.bindValue(":resolucion_resumen", texto_resumido);
    /*
     * esta comprobación es absurda pq realmetne no debería llegar hasta aquí
     * con un capítulo =0; además de que tp deja la BD meter un capítulo NULL..
     */
    if (capitulo != 0)
        query.bindValue(":capitulo", capitulo);
    else
        query.bindValue(":capitulo", QVariant(QVariant::Int));
    query.bindValue(":epigrafe", epigrafe);
    if (!provincia == 0)
        query.bindValue(":provincia", provincia);
    else
        query.bindValue(":provincia", QVariant(QVariant::Int));
    query.bindValue(":entendida", entendido);
    query.bindValue(":volveramirar", volveramirar);
    query.bindValue(":traducida", traducido);
    query.bindValue(":razonada", razonada);
    query.bindValue(":interesante", interesante);
    query.bindValue("resolucion_anterior", resolucion_anterior);
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
