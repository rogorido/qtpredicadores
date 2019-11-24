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
  OBISPO,           // realmente no lo usamos en el form Seleccionar...
  PERSONASGESTION,  // esto es para el form de gestión de personas
  CASASGESTION
};

enum tipodetalles { RESOLUCION, OBRA, PERSONADETALLES, OBISPOS, OTROS };

struct elementopareado {
  int id = 0;
  QString elemento = "";
};

struct fuente {
  int titulo;
  QString tomo;
  QString paginas;
};

typedef QList<QPair<QString, QString>> ExtraInfos;

#endif  // VARIADOS_H
