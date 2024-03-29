#include "resolucionesmodel.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

#include "src/objs/resolucion.h"

ResolucionesModel *ResolucionesModel::pInstance = 0;

ResolucionesModel::ResolucionesModel() : QSqlTableModel()
{
  this->setTable("chapters.resolutions");
  this->select();
}

ResolucionesModel *ResolucionesModel::InstanceModel()
{
  if (pInstance == 0) {
    pInstance = new ResolucionesModel();
    atexit(&DestroyMe);
  }

  return pInstance;
}

void ResolucionesModel::DestroyMe()
{
  if (pInstance != NULL) delete pInstance;
}

bool ResolucionesModel::anadirResolucion(const Resolucion *resolucion)
{
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
  QStringList verbos = resolucion->getVerbos();
  QStringList expresiones = resolucion->getExpresiones();
  QString pages = resolucion->getPages();
  QString notas = resolucion->getNotas();

  QString verbos_final;
  QString expresiones_final;

  if (!verbos.isEmpty()) {
    verbos_final = '{' + verbos.join(", ") + '}';
  }

  if (!expresiones.isEmpty()) {
    expresiones_final = '{' + expresiones.join(", ") + '}';
  }

  query.prepare(
      "INSERT INTO chapters.resolutions(resolution_text, "
      "resolution_traduction, resolution_summary, chapter, "
      "small_title, understood, look_again, province_id, translated, "
      "motivated, interesting, verbs, expressions, "
      "resolution_previous, notes, pages) "
      "VALUES(:resolucion_texto, :resolucion_traduccion, :resolucion_resumen, "
      ":capitulo, "
      ":epigrafe, :entendida, :volveramirar, :provincia, :traducida, "
      ":razonada, :interesante, :verbos, :expresiones, "
      ":resolucion_anterior, :notas, :paginas)");
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
  if (!verbos_final.isEmpty())
    query.bindValue(":verbos", verbos_final);
  else
    query.bindValue(":verbos", QVariant(QVariant::String));
  if (!expresiones_final.isEmpty())
    query.bindValue(":expresiones", expresiones_final);
  else
    query.bindValue(":expresiones", QVariant(QVariant::String));
  query.bindValue("resolucion_anterior", resolucion_anterior);
  query.bindValue(":notas", notas);
  query.bindValue(":paginas", pages);

  if (!query.exec()) {
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

bool ResolucionesModel::actualizarResolucion(const Resolucion *resolucion,
                                             const int resolucionid)
{
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
  QStringList verbos = resolucion->getVerbos();
  QStringList expresiones = resolucion->getExpresiones();
  QString pages = resolucion->getPages();
  QString notas = resolucion->getNotas();

  QString verbos_final;
  QString expresiones_final;

  if (!verbos.isEmpty()) {
    verbos_final = '{' + verbos.join(", ") + '}';
  }

  if (!expresiones.isEmpty()) {
    expresiones_final = '{' + expresiones.join(", ") + '}';
  }

  query.prepare(
      "UPDATE resolutions SET resolution_text = :resolucion_texto, "
      "resolution_traduction = :resolucion_traduccion, "
      "resolution_summary = :resolucion_resumen, "
      "chapter = :capitulo, small_title = :epigrafe, "
      "understood = :entendida, look_again = :volveramirar, "
      "province_id = :provincia, translated = :traducida, "
      "motivated = :razonada, interesting = :interesante,  "
      "verbs = :verbos, expressions = :expresiones, "
      "resolution_previous = :resolucion_anterior, notes = :notas, "
      "pages = :paginas "
      "WHERE resolution_id = :resolutionid");
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
  if (!verbos_final.isEmpty())
    query.bindValue(":verbos", verbos_final);
  else
    query.bindValue(":verbos", QVariant(QVariant::String));
  if (!expresiones_final.isEmpty())
    query.bindValue(":expresiones", expresiones_final);
  else
    query.bindValue(":expresiones", QVariant(QVariant::String));
  query.bindValue("resolucion_anterior", resolucion_anterior);
  query.bindValue(":notas", notas);
  query.bindValue(":paginas", pages);
  query.bindValue(":resolutionid", resolucionid);

  if (!query.exec()) {
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

Resolucion *ResolucionesModel::cargarResolucion(const int resolucionid)
{
  QSqlQuery query;
  Resolucion *resolucion = new Resolucion();

  query.prepare(
      "SELECT * from resolutions WHERE resolution_id = :resolution_id");
  query.bindValue(":resolution_id", resolucionid);

  if (!query.exec()) {
    qDebug() << query.lastError();
    qDebug() << "esta es la query: " << query.executedQuery().toUtf8();

    return resolucion;
  }
  else {
    query.first();

    resolucion->setTexto(query.value(1).toString());
    resolucion->setTextoResumido(query.value(3).toString());
    resolucion->setTextoTraducido(query.value(2).toString());
    resolucion->setCapitulo(query.value(4).toInt());
    resolucion->setEpigrafe(query.value(5).toString());
    resolucion->setProvincia(query.value(6).toInt());
    resolucion->setEntendido(query.value(7).toBool());
    resolucion->setVolverMirar(query.value(8).toBool());
    resolucion->setTraducido(query.value(9).toBool());
    resolucion->setRazonada(query.value(14).toBool());
    resolucion->setInteres(query.value(10).toInt());
    resolucion->setPages(query.value(17).toString());
    resolucion->setNotas(query.value(12).toString());

    return resolucion;
  }
}
