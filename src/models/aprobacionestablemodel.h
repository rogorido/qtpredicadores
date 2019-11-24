#ifndef APROBACIONESTABLEMODEL_H
#define APROBACIONESTABLEMODEL_H

#include <src/objs/aprobacion.h>

#include <QAbstractTableModel>

class AprobacionesTableModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit AprobacionesTableModel(QObject *parent = 0);

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QList<Aprobacion *> getLista();

  void anadirAprobacion(Aprobacion *aprobracion);
  void quitarAprobacion(const int row);

 private:
  QList<Aprobacion *> lista_aprobaciones;
};

#endif  // APROBACIONESTABLEMODEL_H
