#ifndef CASASMODEL_H
#define CASASMODEL_H

#include <QIcon>
#include <QSqlQueryModel>

class Casa;

class CasasModel : public QSqlQueryModel {
  Q_OBJECT

 public:
  static CasasModel *InstanceModel();
  QVariant data(const QModelIndex &index, int role) const override;

  /*
   * Si se trata de una nueva casa no pasamos el parámetro obra_id
   * y funciona.
   */

  bool AnadirCasa(const Casa *casa, int casa_id = 0);
  Casa *devolverCasa(const int id);

 signals:

  void actualizado();

 protected:
  CasasModel();
  CasasModel(const CasasModel &);
  CasasModel &operator=(const CasasModel &);

 private:
  static CasasModel *pInstance;
  static void DestroyMe();

  void cargarQueryInicial();

  QIcon icono_masculino;
  QIcon icono_femenino;
};

#endif  // CASASMODEL_H
