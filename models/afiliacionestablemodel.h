#ifndef AFILIACIONESTABLEMODEL_H
#define AFILIACIONESTABLEMODEL_H

#include <QAbstractTableModel>

class AfiliacionesTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit AfiliacionesTableModel(QObject *parent = 0);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // AFILIACIONESTABLEMODEL_H