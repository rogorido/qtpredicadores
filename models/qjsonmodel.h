#ifndef QJSONMODEL_H
#define QJSONMODEL_H

#include <QAbstractItemModel>

class QJsonModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit QJsonModel(QObject *parent = 0);

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // QJSONMODEL_H