#ifndef PROXYNOMBRES_H
#define PROXYNOMBRES_H

#include <QSortFilterProxyModel>

class ProxyNombres : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    ProxyNombres(QObject *parent = 0);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
};

#endif // PROXYNOMBRES_H
