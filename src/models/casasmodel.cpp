#include "casasmodel.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

#include "src/objs/casa.h"

CasasModel *CasasModel::pInstance = 0;

CasasModel::CasasModel() : QSqlQueryModel()
{
  cargarQueryInicial();
  /*
   *  estos iconos los defino aquí porque si los carga en el método data()
   * los está cargando cada vez que consulta ese método y va muy lento
   */
  icono_masculino = QIcon(":/icons/icons/masculino.png");
  icono_femenino = QIcon(":/icons/icons/femenino.png");
}

CasasModel *CasasModel::InstanceModel()
{
  if (pInstance == 0) {
    pInstance = new CasasModel();
    atexit(&DestroyMe);
  }

  return pInstance;
}

QVariant CasasModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid()) return QVariant();

  QVariant value = QSqlQueryModel::data(index, role);

  if (role == Qt::DecorationRole && index.column() == 1) {
    QModelIndex i = index.model()->index(index.row(), 6);
    bool masculino = QSqlQueryModel::data(i, Qt::DisplayRole).toBool();
    if (masculino)
      return icono_masculino;
    else
      return icono_femenino;
  }

  return value;
}

void CasasModel::DestroyMe()
{
  if (pInstance != NULL) delete pInstance;
}

void CasasModel::cargarQueryInicial()
{
  this->setQuery("SELECT * FROM vistas.houses_alternatives");
}

bool CasasModel::AnadirCasa(const Casa *casa, int casa_id)
{
  QSqlQuery query;

  QString nombre = casa->getNombre();
  QString nombre_latin = casa->getNombreLatin();
  int lugar = casa->getLugar();
  QString lugar_originario = casa->getLugarOriginario();
  bool masculino = casa->getMasculino();
  QString tipo = casa->getTipo();
  QString congregacion = casa->getCongregacion();
  bool buscado = casa->getBuscado();
  bool wiki = casa->getWiki();
  int provincia = casa->getProvincia();
  QString diocesis = casa->getDiocesis();
  QString fecha_fundacion = casa->getFechaFundacion();
  QString fecha_eliminacion = casa->getFechaEliminacion();
  QString advocacion = casa->getAdvocacion();
  bool quetif = casa->getQuetif();
  // este  sería interesante hacerlo con QJson...
  // QString otrosnombres;
  QString notas = casa->getNotas();
  QString otrosdatos = casa->getOtrosDatos();
  bool studiumgenerale = casa->getStudiumgenerale();

  if (casa_id == 0) {
    query.prepare(
        "INSERT INTO general.houses(name, latin_name, place_id, "
        "original_place, men, "
        "type_house, congregation, lookedup, wikipedia, province_id, diocese, "
        "date_foundation, "
        "date_elimination, quetif, advocation, studiumgenerale, notes, "
        "other_data) "
        "VALUES(:nombre, :nombre_latin, :lugar, :lugaroriginario, :masculino, "
        ":tipo, :congregacion, :buscado, :wiki, :provincia_id, :diocesis, "
        ":fecha_fundacion, "
        ":fecha_eliminacion, :quetif, :advocacion, :studiumgenerale, :notas, "
        ":otrosdatos)");
  }
  else {
    query.prepare(
        "UPDATE general.houses SET(name, latin_name, place_id, original_place, "
        "men, "
        "type_house, congregation, lookedup, wikipedia, province_id, diocese, "
        "date_foundation, "
        "date_elimination, quetif, advocation, studiumgenerale, notes, "
        "other_data) "
        "= (:nombre, :nombre_latin, :lugar, :lugaroriginario, :masculino, "
        ":tipo, :congregacion, :buscado, :wiki, :provincia_id, :diocesis, "
        ":fecha_fundacion, "
        ":fecha_eliminacion, :quetif, :advocacion, :studiumgenerale, :notas, "
        ":otrosdatos) "
        "WHERE house_id = :house_id");
  }
  query.bindValue(":nombre", nombre);
  query.bindValue(":nombre_latin", nombre_latin);
  if (lugar != 0)
    query.bindValue(":lugar", lugar);
  else
    query.bindValue(":lugar", QVariant(QVariant::Int));
  query.bindValue(":lugaroriginario", lugar_originario);
  query.bindValue(":masculino", masculino);
  query.bindValue(":tipo", tipo);
  query.bindValue(":congregacion", congregacion);
  query.bindValue(":buscado", buscado);
  query.bindValue(":wiki", wiki);
  if (provincia != 0)
    query.bindValue(":provincia_id", provincia);
  else
    query.bindValue(":provincia_id", QVariant(QVariant::Int));
  query.bindValue(":diocesis", diocesis);
  query.bindValue(":fecha_fundacion", fecha_fundacion);
  query.bindValue(":fecha_eliminacion", fecha_eliminacion);
  query.bindValue(":quetif", quetif);
  query.bindValue(":advocacion", advocacion);
  query.bindValue(":studiumgeneral", studiumgenerale);
  query.bindValue(":notas", notas);

  if (!otrosdatos.isEmpty())
    query.bindValue(":otrosdatos", otrosdatos);
  else
    query.bindValue(":otrosdatos", QVariant(QVariant::String));

  // el id en caso de que estemos actualizando...
  if (casa_id != 0) query.bindValue(":house_id", casa_id);

  if (!query.exec()) {
    qDebug() << query.lastError();
    qDebug() << "esta es la query: " << query.executedQuery().toUtf8();

    return false;
  }
  else {
    cargarQueryInicial();
    emit(actualizado());
    return true;
  }
}

Casa *CasasModel::devolverCasa(const int casa_id)
{
  QSqlQuery query;
  Casa *casa = new Casa();

  query.prepare("SELECT * FROM houses WHERE house_id = :id");
  query.bindValue(":id", casa_id);

  if (!query.exec()) {
    qDebug() << query.lastError();
    qDebug() << "esta es la query: " << query.executedQuery().toUtf8();
    return casa;
  }

  query.first();

  casa->setId(casa_id);
  casa->setNombre(query.value(Casa::CamposCasa::NOMBRE).toString());
  casa->setLugar(query.value(Casa::CamposCasa::PLACEID).toInt());
  casa->setLugarOriginario(
      query.value(Casa::CamposCasa::ORIGINALPLACE).toString());
  casa->setMasculino(query.value(Casa::CamposCasa::MEN).toBool());
  casa->setTipo(query.value(Casa::CamposCasa::TYPEHOUSE).toString());
  casa->setCongregacion(query.value(Casa::CamposCasa::CONGREGATION).toString());
  casa->setStudiumgenerale(
      query.value(Casa::CamposCasa::STUDIUMGENERALE).toBool());
  casa->setWiki(query.value(Casa::CamposCasa::WIKIPEDIA).toBool());
  casa->setBuscado(query.value(Casa::CamposCasa::LOOKEDUP).toBool());
  casa->setProvincia(query.value(Casa::CamposCasa::PROVINCEID).toInt());
  casa->setDiocesis(query.value(Casa::CamposCasa::DIOCESE).toString());
  casa->setFechaFundacion(
      query.value(Casa::CamposCasa::DATEFOUNDATION).toString());
  casa->setAdvocacion(query.value(Casa::CamposCasa::ADVOCATION).toString());
  casa->setNotas(query.value(Casa::CamposCasa::NOTES).toString());
  casa->setQuetif(query.value(Casa::CamposCasa::QUETIF).toBool());
  casa->setFechaEliminacion(
      query.value(Casa::CamposCasa::DATEELIMINATION).toString());

  return casa;
}
