#include "lugaresmodel.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

#include "src/objs/lugar.h"

LugaresModel *LugaresModel::pInstance = 0;

LugaresModel::LugaresModel() : QSqlTableModel()
{
  this->setTable("places");
  this->select();
}

LugaresModel *LugaresModel::InstanceModel()
{
  if (pInstance == 0) {
    pInstance = new LugaresModel();
    atexit(&DestroyMe);
  }

  return pInstance;
}

void LugaresModel::DestroyMe()
{
  if (pInstance != NULL) delete pInstance;
}

void LugaresModel::AnadirLugar(const QString &lugar, const QString &lugar_latin,
                               const QString &pais)
{
  QSqlQuery query;

  qDebug() << lugar << pais;

  query.prepare(
      "INSERT INTO general.places(place, place_latin, country) VALUES(:lugar, "
      ":lugar_latin, :pais)");
  query.bindValue(":lugar", lugar);
  query.bindValue(":lugar_latin", lugar_latin);
  query.bindValue(":pais", pais);
  query.exec();

  this->select();
  emit(actualizado());
}

void LugaresModel::AnadirLugar(const QString &lugar, const QString &lugar_latin,
                               const QString &pais, const QString &otrosnombres)
{
  QSqlQuery query;

  query.prepare(
      "INSERT INTO general.lugares(place, place_latin, country, other_names) "
      "VALUES(:lugar, :lugar_latin, :pais, :otrosnombres)");
  query.bindValue(":lugar", lugar);
  query.bindValue(":lugar_latin", lugar_latin);
  query.bindValue(":pais", pais);
  query.bindValue(":otrosnombres", otrosnombres);
  query.exec();

  this->select();

  emit(actualizado());
}

bool LugaresModel::AnadirLugar(const Lugar *lugar)
{
  QSqlQuery query;

  QString nombre_lugar = lugar->getLugar();
  QString latin_lugar = lugar->getLugarLatin();
  QString pais = lugar->getPais();
  QString wikidata = lugar->getWikidata();
  QString otrosnombres = lugar->getOtrosNombres();
  QString tipo_lugar = lugar->getTipoLugar();

  query.prepare(
      "INSERT INTO general.places(place, place_latin, country, wikidata, "
      "other_names, type_place) "
      "VALUES(:lugar, :lugar_latin, :pais, :wikidata, :otrosnombres, "
      ":tipo_lugar)");
  query.bindValue(":lugar", nombre_lugar);
  query.bindValue(":lugar_latin", latin_lugar);
  query.bindValue(":pais", pais);
  query.bindValue(":wikidata", wikidata);
  query.bindValue(":otrosnombres", otrosnombres);
  query.bindValue(":tipo_lugar", tipo_lugar);

  if (!query.exec()) {
    qDebug() << query.lastError();
    return false;
  }
  else {
    this->select();
    emit(actualizado());
    return true;
  }
}

Lugar LugaresModel::devolverLugar(const int id)
{
  QSqlQuery query;
  Lugar lugar;

  query.prepare("SELECT * FROM places WHERE place_id = :id");
  query.bindValue(":id", id);

  if (!query.exec()) {
    qDebug() << query.lastError();
    qDebug() << "esta es la query: " << query.executedQuery().toUtf8();
    return lugar;
  }

  query.first();

  // solo metemos esto que es lo que necesito ahora...
  lugar.setId(id);
  lugar.setLugar(query.value(1).toString());

  return lugar;
}
