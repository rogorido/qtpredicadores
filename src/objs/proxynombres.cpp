#include "proxynombres.h"

ProxyNombres::ProxyNombres(tiposeleccionar tipo, QObject *parent)
    : QSortFilterProxyModel(parent), tipoproxy(tipo)
{
  /*
   *  estos iconos los defino aquí porque si los carga en el método data()
   * los está cargando cada vez que consulta ese método y va muy lento
   */
  icono_masculino = QIcon(":/icons/icons/masculino.png");
  icono_femenino = QIcon(":/icons/icons/femenino.png");
}

QVariant ProxyNombres::data(const QModelIndex &index, int role) const
{
  if (!index.isValid()) return QVariant();

  QVariant value = QSortFilterProxyModel::data(index, role);

  if (role == Qt::DecorationRole && index.column() == 1) {
    switch (tipoproxy) {
      case CASA: {
        QModelIndex i = index.model()->index(index.row(), 6);
        bool masculino =
            QSortFilterProxyModel::data(i, Qt::DisplayRole).toBool();
        if (masculino)
          return icono_masculino;
        else
          return icono_femenino;
      }

      case PERSONA:
      case PERSONASGESTION: {
        QModelIndex i = index.model()->index(index.row(), 4);
        bool masculino =
            QSortFilterProxyModel::data(i, Qt::DisplayRole).toBool();
        if (masculino)
          return icono_masculino;
        else
          return icono_femenino;
      }
    }
  }

  return value;
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
  QModelIndex index9 = sourceModel()->index(sourceRow, 9, sourceParent);
  QModelIndex index10 = sourceModel()->index(sourceRow, 10, sourceParent);
  QModelIndex index11 = sourceModel()->index(sourceRow, 11, sourceParent);
  QModelIndex index12 = sourceModel()->index(sourceRow, 12, sourceParent);

  switch (tipoproxy) {
    case PERSONA:

      return sourceModel()->data(index1).toString().contains(filterRegExp()) ||
             sourceModel()->data(index2).toString().contains(filterRegExp()) ||
             sourceModel()->data(index3).toString().contains(filterRegExp()) ||
             sourceModel()->data(index5).toString().contains(filterRegExp()) ||
             sourceModel()->data(index6).toString().contains(filterRegExp()) ||
             sourceModel()->data(index8).toString().contains(filterRegExp()) ||
             sourceModel()->data(index9).toString().contains(filterRegExp()) ||
             sourceModel()->data(index10).toString().contains(filterRegExp()) ||
             sourceModel()->data(index11).toString().contains(filterRegExp()) ||
             sourceModel()->data(index12).toString().contains(filterRegExp());
      break;

    case LUGAR:

      return sourceModel()->data(index1).toString().contains(filterRegExp()) ||
             sourceModel()->data(index2).toString().contains(filterRegExp()) ||
             sourceModel()->data(index3).toString().contains(filterRegExp()) ||
             sourceModel()->data(index4).toString().contains(filterRegExp()) ||
             sourceModel()->data(index5).toString().contains(filterRegExp()) ||
             sourceModel()->data(index6).toString().contains(filterRegExp()) ||
             sourceModel()->data(index7).toString().contains(filterRegExp()) ||
             sourceModel()->data(index8).toString().contains(filterRegExp());
      break;

    case CASA:
      return sourceModel()->data(index1).toString().contains(filterRegExp()) ||
             sourceModel()->data(index2).toString().contains(filterRegExp()) ||
             sourceModel()->data(index3).toString().contains(filterRegExp()) ||
             sourceModel()->data(index4).toString().contains(filterRegExp()) ||
             sourceModel()->data(index5).toString().contains(filterRegExp());
      break;

    case PROVINCIA:
      return sourceModel()->data(index1).toString().contains(filterRegExp()) ||
             sourceModel()->data(index2).toString().contains(filterRegExp()) ||
             sourceModel()->data(index3).toString().contains(filterRegExp()) ||
             sourceModel()->data(index4).toString().contains(filterRegExp()) ||
             sourceModel()->data(index5).toString().contains(filterRegExp()) ||
             sourceModel()->data(index6).toString().contains(filterRegExp()) ||
             sourceModel()->data(index7).toString().contains(filterRegExp());
      break;

    case CAPITULO:
      return sourceModel()->data(index1).toString().contains(filterRegExp()) ||
             sourceModel()->data(index2).toString().contains(filterRegExp());
      break;

    case DIOCESIS:
      return sourceModel()->data(index1).toString().contains(filterRegExp()) ||
             sourceModel()->data(index2).toString().contains(filterRegExp()) ||
             sourceModel()->data(index3).toString().contains(filterRegExp()) ||
             sourceModel()->data(index7).toString().contains(filterRegExp());
      break;

    case TEMA:
      return sourceModel()->data(index1).toString().contains(filterRegExp());
      break;

    case OBISPO:
      /*
       * index1 : obispo, index2: diócesis, index4: papa.
       */
      return sourceModel()->data(index1).toString().contains(filterRegExp()) ||
             sourceModel()->data(index2).toString().contains(filterRegExp()) ||
             sourceModel()->data(index4).toString().contains(filterRegExp());
      break;

    case PERSONASGESTION:
      return sourceModel()->data(index1).toString().contains(filterRegExp()) ||
             sourceModel()->data(index2).toString().contains(filterRegExp());
      break;

    case CASASGESTION:
      return sourceModel()->data(index1).toString().contains(filterRegExp()) ||
             sourceModel()->data(index2).toString().contains(filterRegExp()) ||
             sourceModel()->data(index3).toString().contains(filterRegExp()) ||
             sourceModel()->data(index4).toString().contains(filterRegExp()) ||
             sourceModel()->data(index5).toString().contains(filterRegExp());
      break;

    default:  // NOTE: esto no sé si es correcto así...
      return true;
  }
}
