#include "capitulosmodel.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

#include "src/objs/capitulo.h"

CapitulosModel *CapitulosModel::pInstance = 0;

CapitulosModel::CapitulosModel() : QSqlTableModel()
{
  this->setTable("chapters.chapters");
  this->select();
}

CapitulosModel *CapitulosModel::InstanceModel()
{
  if (pInstance == 0) {
    pInstance = new CapitulosModel();
    atexit(&DestroyMe);
  }

  return pInstance;
}

void CapitulosModel::DestroyMe()
{
  if (pInstance != NULL) delete pInstance;
}

bool CapitulosModel::AnadirCapitulo(const Capitulo *capitulo)
{
  QSqlQuery query;

  QString nombre = capitulo->getNombre();
  int lugar = capitulo->getLugar();
  QString tipo = capitulo->getTipo();
  QString asistentes = capitulo->getAsistentes();
  QString volumen = capitulo->getVolumen();
  QString paginas = capitulo->getPaginas();
  QString notas = capitulo->getNotas();
  int maestro = capitulo->getMaestroGeneral();
  bool definitorio = capitulo->getDefinitorio();
  QDate fechainicial = capitulo->getFechaInicio();
  QDate fechafinal = capitulo->getFechaFin();
  int provincia = capitulo->getProvincia();

  query.prepare(
      "INSERT INTO chapters.chapters(general_name, place_id, date_beginning, "
      "date_ending, "
      "definitory, type_chapter, general_master, province_id, attendees, "
      "volume, pages, notes) "
      "VALUES(:nombre, :lugar_id, :fechainicio, :fechafinal, "
      ":definitorio, :tipo, :maestro, :provincia, :asistentes, :tomo, "
      ":paginas, :notas)");
  query.bindValue(":nombre", nombre);
  if (lugar != 0)
    query.bindValue(":lugar_id", lugar);
  else
    query.bindValue(":lugar_id", QVariant(QVariant::Int));
  query.bindValue(":tipo", tipo);
  if (maestro != 0)
    query.bindValue(":maestro", maestro);
  else
    query.bindValue(":maestro", QVariant(QVariant::Int));
  if (provincia != 0)
    query.bindValue(":provincia", provincia);
  else
    query.bindValue(":provincia", QVariant(QVariant::Int));

  query.bindValue(":definitorio", definitorio);
  query.bindValue(":asistentes", asistentes);
  query.bindValue(":fechainicio", fechainicial);
  query.bindValue(":fechafinal", fechafinal);
  query.bindValue(":tomo", volumen);
  query.bindValue(":paginas", paginas);
  query.bindValue(":notas", notas);

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
