#include "obrasmodel.h"

#include <QSqlQuery>

#include "objs/obra.h"

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
    QString notas = obra->getNotas();

    query.prepare("INSERT INTO works(title, language, author_id, type_work, format, "
          "volumes, number_pages, printed, maybe_printed, manuscrit, look_again, "
		  "place_print_original, place_print_id, "
		  "date_print, editor, references_work, reduced_title, "
                  "contents, interesting, dubious, expurgatable, reliability, notes) "
		  " VALUES (:titulo, :idioma, :autor_id, :tipo, :formato, "
          ":tomos, :numero_pags, :impreso, :talvez_impreso, :manuscrito, :volveramirar, "
		  ":lugar_impresion_original, :lugar_impresion_id, "
		  ":fecha_impresion, :editor, :referencias, :tituloreducido, "
          ":contenido, :interesante, :dudoso, :expurgable, :fiabilidad, :notas)");
    query.bindValue(":titulo", titulo);
    query.bindValue(":idioma", idioma);
    query.bindValue(":autor_id", autor);
    query.bindValue(":tipo", tipo);
    query.bindValue(":formato", formato);
    query.bindValue(":impreso", impreso);
    query.bindValue(":talvez_impreso", talvez_impreso);
    query.bindValue(":manuscrito", manuscrito);
    query.bindValue(":volveramirar", volveramirar);
    query.bindValue(":fecha_impresion", fecha);
    query.bindValue(":editor", editor);
    query.bindValue(":referencias", refs);
    query.bindValue(":tomos", tomos);
    query.bindValue(":numero_pags", numeropags);
    query.bindValue(":lugar_impresion_original", lugaroriginal);
    query.bindValue(":lugar_impresion_id", lugar);
    query.bindValue(":tituloreducido", tituloreducido);
    query.bindValue(":contenido", contenido);
    query.bindValue(":interesante", interesante);
    query.bindValue(":dudoso", dudoso);
    query.bindValue(":expurgable", expurgable);
    query.bindValue(":fiabilidad", fiabilidad);
    query.bindValue(":notas", notas);
    query.exec();
    this->select();
}
