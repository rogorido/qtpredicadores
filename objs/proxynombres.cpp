#include "proxynombres.h"

ProxyNombres::ProxyNombres(tiposeleccionar tipo, QObject *parent)
  : QSortFilterProxyModel(parent), tipoproxy(tipo)
{
}

bool ProxyNombres::filterAcceptsRow(int sourceRow,
        const QModelIndex &sourceParent) const
{
    QModelIndex index1 = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex index2 = sourceModel()->index(sourceRow, 2, sourceParent);
    QModelIndex index3 = sourceModel()->index(sourceRow, 3, sourceParent);
    QModelIndex index4 = sourceModel()->index(sourceRow, 4, sourceParent);
    QModelIndex index5 = sourceModel()->index(sourceRow, 5, sourceParent);
    QModelIndex index6 = sourceModel()->index(sourceRow, 6, sourceParent);
    QModelIndex index7 = sourceModel()->index(sourceRow, 7, sourceParent);
    QModelIndex index8 = sourceModel()->index(sourceRow, 8, sourceParent);

  switch(tipoproxy) {
  case PERSONA:

    return sourceModel()->data(index1).toString().contains(filterRegExp())
            || sourceModel()->data(index2).toString().contains(filterRegExp())
            || sourceModel()->data(index3).toString().contains(filterRegExp())
            || sourceModel()->data(index4).toString().contains(filterRegExp())
            || sourceModel()->data(index5).toString().contains(filterRegExp())
            || sourceModel()->data(index6).toString().contains(filterRegExp())
            || sourceModel()->data(index7).toString().contains(filterRegExp())
            || sourceModel()->data(index8).toString().contains(filterRegExp());
    break;

  case LUGAR:

      return sourceModel()->data(index1).toString().contains(filterRegExp())
              || sourceModel()->data(index2).toString().contains(filterRegExp())
              || sourceModel()->data(index3).toString().contains(filterRegExp())
              || sourceModel()->data(index4).toString().contains(filterRegExp())
              || sourceModel()->data(index5).toString().contains(filterRegExp())
              || sourceModel()->data(index6).toString().contains(filterRegExp())
              || sourceModel()->data(index7).toString().contains(filterRegExp())
              || sourceModel()->data(index8).toString().contains(filterRegExp());
      break;

  case CASA:
      return sourceModel()->data(index1).toString().contains(filterRegExp())
              || sourceModel()->data(index2).toString().contains(filterRegExp())
              || sourceModel()->data(index3).toString().contains(filterRegExp())
              || sourceModel()->data(index4).toString().contains(filterRegExp())
              || sourceModel()->data(index5).toString().contains(filterRegExp());
      break;

  case PROVINCIA:
      return sourceModel()->data(index1).toString().contains(filterRegExp())
              || sourceModel()->data(index2).toString().contains(filterRegExp())
              || sourceModel()->data(index3).toString().contains(filterRegExp())
              || sourceModel()->data(index4).toString().contains(filterRegExp())
              || sourceModel()->data(index5).toString().contains(filterRegExp())
              || sourceModel()->data(index6).toString().contains(filterRegExp())
              || sourceModel()->data(index7).toString().contains(filterRegExp());
      break;
  case CAPITULO:
      return sourceModel()->data(index1).toString().contains(filterRegExp())
              || sourceModel()->data(index2).toString().contains(filterRegExp());
      break;
  case TEMA:
      return sourceModel()->data(index1).toString().contains(filterRegExp());
      break;

  }

}
