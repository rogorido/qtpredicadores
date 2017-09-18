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
    TEMA,
    DIOCESIS,
    OBISPO  // realmente no lo usamos en el form Seleccionar...
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

struct fuente {
    int titulo;
    QString tomo;
    QString paginas;
};

typedef QList<QPair<QString,QString>> ExtraInfos;

#endif // VARIADOS_H
