#include "aprobacionestablemodel.h"

AprobacionesTableModel::AprobacionesTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant AprobacionesTableModel::headerData(int section, Qt::Orientation orientation, int role) const{

    if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return tr("Aprobación");
                case 1:
                return tr("Persona/Casa");

                case 2:
                    return tr("Provincia");

                default:
                    return QVariant();
            }
        }
        return QVariant();
}

int AprobacionesTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return lista_aprobaciones.size();
}

int AprobacionesTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

QVariant AprobacionesTableModel::data(const QModelIndex &index, int role) const
{
    QString persona;
    QString casa;

    if (!index.isValid())
        return QVariant();

    if (index.row() >= lista_aprobaciones.size() || index.row() < 0)
            return QVariant();

    if (role == Qt::DisplayRole) {
            Aprobacion *aprobacion = lista_aprobaciones.at(index.row());
            if (aprobacion->getTipoAprobacion() == Aprobacion::TipoAprobacion::PERSONA)
                persona = aprobacion->getPersona().getNombre() + ' ' + aprobacion->getPersona().getApellidos();
            else
                casa = aprobacion->getCasa().getNombre();

            if (index.column() == 0){
                if (aprobacion->getTipoAprobacion() == Aprobacion::TipoAprobacion::PERSONA)
                    return aprobacion->getCargo();
                else
                    return aprobacion->getTipoInstitucion();
            }
            else if (index.column() == 1){
                    if (aprobacion->getTipoAprobacion() == Aprobacion::TipoAprobacion::PERSONA)
                        return persona;
                    else
                        return casa;
            }
            else if (index.column() == 2)
                return aprobacion->getProvincia().getNombre();
        }

    return QVariant();
}

QList<Aprobacion*> AprobacionesTableModel::getLista()
{
    return lista_aprobaciones;
}

void AprobacionesTableModel::anadirAprobacion(Aprobacion *aprobracion)
{
    /*
     * esto así creo que es una chapuza
     */
    beginResetModel();
    lista_aprobaciones.append(aprobracion);
    endResetModel();
    //emitdataChanged(QModelIndex idx, QModelIndex idx2));
}

void AprobacionesTableModel::quitarAprobacion(const int row)
{
    /*
     * esto así creo que es una chapuza
     */
    beginResetModel();
    removeRow(row);
    endResetModel();

    lista_aprobaciones.removeAt(row);
}
