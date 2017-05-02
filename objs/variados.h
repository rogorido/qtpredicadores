#ifndef VARIADOS_H
#define VARIADOS_H

#include <QList>
#include <QPair>
#include <QString>

enum tiposeleccionar {
    CASA,
    PERSONA,
    PROVINCIA,
    LUGAR,
    CAPITULO,
    TEMA
};

enum tipodetalles {
    RESOLUCION,
    OBRA,
    PERSONADETALLES,
    OTROS
};

struct elementopareado{
  int id = 0;
  QString elemento = "";
};

typedef QList<QPair<QString,QString>> ExtraInfos;

#endif // VARIADOS_H
