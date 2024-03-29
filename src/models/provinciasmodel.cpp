#include "provinciasmodel.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

#include "src/objs/provincia.h"

ProvinciasModel *ProvinciasModel::pInstance = 0;

ProvinciasModel::ProvinciasModel() : QSqlTableModel()
{
  this->setTable("provinces");
  this->select();
}

ProvinciasModel *ProvinciasModel::InstanceModel()
{
  if (pInstance == 0) {
    pInstance = new ProvinciasModel();
    atexit(&DestroyMe);
  }

  return pInstance;
}

void ProvinciasModel::DestroyMe()
{
  if (pInstance != NULL) delete pInstance;
}

bool ProvinciasModel::AnadirProvincia(const Provincia *provincia)
{
  QSqlQuery query;

  /*
   * por ahora he deshabilitado lo de otrosnombres
   * hay que añadirlo
   */
  QString nombre = provincia->getNombre();
  // QString otros_nombres = provincia->getOtrosNombres();
  QString erigida = provincia->getErigida();
  QString notas = provincia->getNotas();

  // if (otros_nombres.isEmpty())
  //    otros_nombres = "{}";

  // query.prepare("INSERT INTO general.provinces(name, other_names, erected,
  // notes) "
  //              "VALUES(:nombre, :otrosnombres, :erigida, :notas)");
  query.prepare(
      "INSERT INTO general.provinces(name, erected, notes) "
      "VALUES(:nombre, :erigida, :notas)");
  query.bindValue(":nombre", nombre);
  // query.bindValue(":otrosnombres", otros_nombres);
  query.bindValue(":erigida", erigida);
  query.bindValue(":notas", notas);

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
