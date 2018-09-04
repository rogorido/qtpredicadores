#include "casasownmodel.h"

#include <QtDebug>

CasasOwnModel::CasasOwnModel(QObject *parent)
    : QSqlQueryModel(parent)
{
    /*
     *  estos iconos los defino aquí porque si los carga en el método data()
     * los está cargando cada vez que consulta ese método y va muy lento
     */
    icono_masculino = QIcon(":/icons/icons/masculino.png");
    icono_femenino = QIcon(":/icons/icons/femenino.png");

}

QVariant CasasOwnModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QVariant value = QSqlQueryModel::data(index, role);

    if (role == Qt::DecorationRole && index.column() == 1) {
        QModelIndex i= index.model()->index(index.row(), 6);
        bool masculino = QSqlQueryModel::data(i, Qt::DisplayRole).toBool();
        if (masculino)
            return icono_masculino;
         else
            return icono_femenino;
    }

    return value;

}
