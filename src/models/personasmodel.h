#ifndef PERSONASMODEL_H
#define PERSONASMODEL_H

#include <QIcon>
#include <QSqlQueryModel>

class Persona;
class QJsonModel;

class PersonasModel : public QSqlQueryModel {
  Q_OBJECT

 public:
  static PersonasModel *InstanceModel();
  QVariant data(const QModelIndex &index, int role) const override;

  /*
   * Si se trata de una nueva obra no pasamos el parámetro persona_id
   * y funciona.
   */
  bool AnadirPersona(const Persona *persona, int persona_id = 0);

  Persona *devolverPersona(const int id);
  // esto devuelve los detalles de una persona
  QJsonModel *devolverDetalles(const int id);

 signals:

  void actualizado();

 protected:
  PersonasModel();
  PersonasModel(const PersonasModel &);
  PersonasModel &operator=(const PersonasModel &);

 private:
  static PersonasModel *pInstance;
  static void DestroyMe();

  void cargarQueryInicial();

  QIcon icono_masculino;
  QIcon icono_femenino;
};

#endif  // PERSONASMODEL_H
