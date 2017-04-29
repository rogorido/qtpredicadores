#ifndef APROBACIONESTABLEMODEL_H
#define APROBACIONESTABLEMODEL_H

#include <QAbstractTableModel>

class AprobacionesTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit AprobacionesTableModel(QObject *parent = 0);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // APROBACIONESTABLEMODEL_H