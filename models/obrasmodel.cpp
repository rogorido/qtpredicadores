#include "obrasmodel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "objs/obra.h"

ObrasModel *ObrasModel::pInstance = 0;

ObrasModel::ObrasModel() :
    QSqlTableModel()
{
    this->setTable("works.works");
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

bool ObrasModel::AnadirObra(const Obra *obra){
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

    if (!query.exec()){
        qDebug() << query.lastError();
        return false;
    }
    else {
        this->select();
        return true;
    }

}
