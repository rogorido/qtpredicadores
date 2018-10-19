#ifndef PROXYNOMBRES_H
#define PROXYNOMBRES_H

#include <QSortFilterProxyModel>
#include <QIcon>

#include "objs/variados.h"

class ProxyNombres : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    ProxyNombres(tiposeleccionar tipo, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const override;

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:

    /*
       una int que nos permite usar el modelo con diversos modelos base:
       1. 0 es para los nombres de autores
       2. 1 es para los nombres de lugares
    */
    
    tiposeleccionar tipoproxy;

    QIcon icono_masculino;
    QIcon icono_femenino;
};

#endif // PROXYNOMBRES_H
