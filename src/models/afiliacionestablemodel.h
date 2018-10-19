#ifndef AFILIACIONESTABLEMODEL_H
#define AFILIACIONESTABLEMODEL_H

#include <QAbstractTableModel>

#include "src/objs/variados.h"
#include "src/objs/afiliacion.h"

class AfiliacionesTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit AfiliacionesTableModel(QObject *parent = 0);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QList<Afiliacion *> getLista();

    void anadirAfiliacion(Afiliacion *afiliacion);
    void quitarAfiliacion(const int row);

private:

      QList<Afiliacion *> lista_afiliaciones;

};

#endif // AFILIACIONESTABLEMODEL_H
