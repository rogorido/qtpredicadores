#ifndef SQLFILTROGESTOR_H
#define SQLFILTROGESTOR_H

#include <QMap>
#include <QObject>

class SqlFiltroGestor : public QObject {
  Q_OBJECT
 public:
  explicit SqlFiltroGestor(QString sql, QObject *parent = nullptr);

  void setSqlGeneral(QString sql);
  void setSqlOrder(QString sql);
  void anadirFiltro(QString nombre, QString sql);
  void quitarFiltro(QString nombre);
  void borrarFiltros();

 signals:

  void actualizadoSqlFiltroGestor(QString s);

 private:
  /*
   * guardamos los filtros con su nombre
   * y el código SQL. Como es un QMap entiendo que no es necesario
   * borrar un filtro que tenga el mismo nombre. Es decir, que para actualizar
   * un filtro no es necesario borrarlo, sino que al pasarle el mismo "key"
   * lo reemplaza.
   */
  QMap<QString, QString> filtros_map;

  /*
   * Aquí está el SQL general que llega
   * del formulario.
   */
  QString sql_basico;

  /*
   * este es el SQL que creamos
   */
  QString sql_creado;

  /*
   * Aquí está el SQL que sirve para ordenar
   */
  QString sql_order;

  void generarSql();
};

#endif  // SQLFILTROGESTOR_H
