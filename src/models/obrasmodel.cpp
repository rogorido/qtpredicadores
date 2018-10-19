#include "obrasmodel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#include "src/objs/obra.h"
#include "src/models/qjsonmodel.h"

ObrasModel *ObrasModel::pInstance = 0;

ObrasModel::ObrasModel() :
    QSqlTableModel()
{
    this->setTable("works.works");
    this->select();
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

bool ObrasModel::AnadirObra(const Obra *obra, int obra_id){
    QSqlQuery query;

    QString titulo = obra->getTitulo();
    QString idioma = obra->getIdioma();
    int autor = obra->getAutor();
    QString tipo = obra->getTipo();
    QString formato = obra->getFormato();
    int tomos = obra->getTomos();
    QString numeropags = obra->getNumeroPags();
    bool impreso = obra->getImpreso();
    bool talvez_impreso = obra->getTalVezImpreso();
    bool manuscrito = obra->getManuscrito();
    QString lugaroriginal = obra->getLugarOriginal();
    int lugar = obra->getLugar();
    int fecha = obra->getFecha();
    QString editor = obra->getEditor();
    bool refs = obra->getReferencias();
    bool tituloreducido = obra->getTituloReducido();
    bool contenido = obra->getContenido();
    int interesante = obra->getInteresante();
    bool dudoso = obra->getDudoso();
    bool expurgable = obra->getExpurgable();
    int fiabilidad = obra->getFiabilidad();
    bool volveramirar = obra->getVolverMirar();
    bool investigar = obra->getInvestigar();
    QString traduccion = obra->getTraduccion();
    QString pagequetif = obra->getPageQuetif();
    QString notas = obra->getNotas();

    if (obra_id == 0) {
        query.prepare("INSERT INTO works.works(title, language_work, author_id, type_work, format, "
                      "volumes, number_pages, printed, maybe_printed, manuscrit, look_again, investigate, "
                      "place_print_original, place_print_id, "
                      "date_print, editor, references_work, reduced_title, traduction, "
                      "contents, interesting, dubious, expurgatable, reliability, page_quetif, notes) "
                      " VALUES (:titulo, :idioma, :autor_id, :tipo, :formato, "
                      ":tomos, :numero_pags, :impreso, :talvez_impreso, :manuscrito, :volveramirar, :investigar, "
                      ":lugar_impresion_original, :lugar_impresion_id, "
                      ":fecha_impresion, :editor, :referencias, :tituloreducido, :traduccion, "
                      ":contenido, :interesante, :dudoso, :expurgable, :fiabilidad, :pagequetif, :notas)");
    }
    else {
        query.prepare("UPDATE works.works SET(title, language_work, author_id, type_work, format, "
                      "volumes, number_pages, printed, maybe_printed, manuscrit, look_again, investigate, "
                      "place_print_original, place_print_id, "
                      "date_print, editor, references_work, reduced_title, traduction, "
                      "contents, interesting, dubious, expurgatable, reliability, page_quetif, notes) "
                      " = (:titulo, :idioma, :autor_id, :tipo, :formato, "
                      ":tomos, :numero_pags, :impreso, :talvez_impreso, :manuscrito, :volveramirar, :investigar, "
                      ":lugar_impresion_original, :lugar_impresion_id, "
                      ":fecha_impresion, :editor, :referencias, :tituloreducido, :traduccion, "
                      ":contenido, :interesante, :dudoso, :expurgable, :fiabilidad, :pagequetif, :notas) "
                      "WHERE work_id = :work_id");
    }

    // ahora ponemos los campos...
    query.bindValue(":titulo", titulo);
    query.bindValue(":idioma", idioma);
    if (!autor == 0)
        query.bindValue(":autor_id", autor);
    else
        query.bindValue(":autor_id", QVariant(QVariant::Int));
    query.bindValue(":tipo", tipo);
    query.bindValue(":formato", formato);
    query.bindValue(":impreso", impreso);
    query.bindValue(":talvez_impreso", talvez_impreso);
    query.bindValue(":manuscrito", manuscrito);
    query.bindValue(":volveramirar", volveramirar);
    query.bindValue(":investigar", investigar);
    query.bindValue(":fecha_impresion", fecha);
    query.bindValue(":editor", editor);
    query.bindValue(":referencias", refs);
    query.bindValue(":tomos", tomos);
    query.bindValue(":numero_pags", numeropags);
    query.bindValue(":lugar_impresion_original", lugaroriginal);
    if (!lugar == 0)
        query.bindValue(":lugar_impresion_id", lugar);
    else
        query.bindValue(":lugar_impresion_id", QVariant(QVariant::Int));
    query.bindValue(":tituloreducido", tituloreducido);
    query.bindValue(":traduccion", traduccion);
    query.bindValue(":contenido", contenido);
    query.bindValue(":interesante", interesante);
    query.bindValue(":dudoso", dudoso);
    query.bindValue(":expurgable", expurgable);
    query.bindValue(":fiabilidad", fiabilidad);
    query.bindValue(":pagequetif", pagequetif);
    query.bindValue(":notas", notas);

    // el work_id para el caso de que sea un update...
    if (obra_id != 0)
        query.bindValue(":work_id", obra_id);

    if (!query.exec()){
        qDebug() << query.lastError();
        return false;
    }
    else {
        this->select();
        return true;
    }

}

Obra *ObrasModel::devolverObra(const int id)
{
    QSqlQuery query;
    Obra *obra = new Obra();
    QString json_otros;
    QJsonDocument json_doc;

    query.prepare("SELECT * FROM works WHERE work_id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << query.lastError();
        qDebug() << "esta es la query: " << query.executedQuery().toUtf8();
        return obra;
    }

    query.first();

    obra->setId(id);
    obra->setTitulo(query.value(Obra::CamposObra::TITLE).toString());
    obra->setIdioma(query.value(Obra::CamposObra::LANGUAGE_WORK).toString());
    obra->setAutor(query.value(Obra::CamposObra::AUTHOR_ID).toInt());
    obra->setTipo(query.value(Obra::CamposObra::TYPE_WORK).toString());
    obra->setFormato(query.value(Obra::CamposObra::FORMAT).toString());
    obra->setTomos(query.value(Obra::CamposObra::VOLUMES).toInt());
    obra->setNumeroPags(query.value(Obra::CamposObra::NUMBER_PAGES).toString());
    obra->setImpreso(query.value(Obra::CamposObra::PRINTED).toBool());
    obra->setTalVezImpreso(query.value(Obra::CamposObra::MAYBE_PRINTED).toBool());
    obra->setManuscrito(query.value(Obra::CamposObra::MANUSCRIT).toBool());
    obra->setLugarOriginal(query.value(Obra::CamposObra::PLACE_PRINT_ORIGINAL).toString());
    obra->setLugar(query.value(Obra::CamposObra::PLACE_PRINT_ID).toInt());
    obra->setFecha(query.value(Obra::CamposObra::DATE_PRINT).toInt());
    obra->setEditor(query.value(Obra::CamposObra::EDITOR).toString());
    obra->setTraduccion(query.value(Obra::CamposObra::TRADUCTION).toString());
    obra->setReferencias(query.value(Obra::CamposObra::REFERENCES_WORK).toBool());
    obra->setTituloReducido(query.value(Obra::CamposObra::REDUCED_TITLE).toBool());
    obra->setContenido(query.value(Obra::CamposObra::CONTENTS).toBool());
    obra->setInteresante(query.value(Obra::CamposObra::INTERESTING).toInt());
    obra->setDudoso(query.value(Obra::CamposObra::DUBIOUS).toBool());
    obra->setVolverMirar(query.value(Obra::CamposObra::LOOK_AGAIN).toBool());
    obra->setExpurgable(query.value(Obra::CamposObra::EXPURGATABLE).toBool());
    obra->setFiabilidad(query.value(Obra::CamposObra::RELIABILITY).toInt());
    obra->setNotas(query.value(Obra::CamposObra::NOTES).toString());
    obra->setPageQuetif(query.value(Obra::CamposObra::PAGE_QUETIF).toString());
    obra->setInvestigar(query.value(Obra::CamposObra::INVESTIGATE).toBool());

    return obra;

}

QVector<int> ObrasModel::materiasObra(const int obra_id)
{
    QSqlQuery query;
    QVector<int> temas;

    QString sql = QString("SELECT * FROM works_themes WHERE work_id = %1").arg(obra_id);

    if (!query.exec(sql)) {
        qDebug() << query.lastError();
        qDebug() << "esta es la query: " << query.executedQuery().toUtf8();
        return temas;
    }

    while (query.next()) {
        temas.append(query.value(2).toInt());
    }

    return temas;

}

QJsonModel *ObrasModel::devolverDetalles(const int id)
{
    QSqlQuery query;
    QString sql;
    QJsonModel *json_model = new QJsonModel();
    QJsonDocument json;

    sql = QString("SELECT details FROM works_details WHERE work_id=%1").arg(id);
    query.exec(sql);

    /*
     * joder, que lío hay que hacer para construir un json...
     * hay que usar eso de QByteArray pq con una QString normal
     * no hay manera...
     */
    while (query.next()) {
        QByteArray datos = query.value(0).toByteArray();
        json = QJsonDocument::fromJson(datos);
        /*
         * tenemos que pasar json.object que construye un
         * QjsonObject, que es al parecer tb un QJsonValue
         * y es lo que pide anadirJson...
         */
        json_model->anadirJson(json.object());
    }

    json_model->resetearModelo();

    return json_model;

}
