#ifndef VARIADOS_H
#define VARIADOS_H

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

#endif // VARIADOS_H
