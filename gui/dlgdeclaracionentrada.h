#ifndef DLGDECLARACIONENTRADA_H
#define DLGDECLARACIONENTRADA_H

#include <QDialog>

#include "objs/variados.h"
#include "objs/pena.h"
#include "objs/infraccion.h"
#include "objs/declaracion.h"

/*
 * Tengo el problema de que no sé cómo borrar una infracción o una pena
 * pq al ser un objeto no sé cómo borrarlo...
 * Tal vez habría que hacerlo en la clase con un reset o algo así...
 */

namespace Ui {
class dlgDeclaracionEntrada;
}

class dlgDeclaracionEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgDeclaracionEntrada(QWidget *parent = 0);
    ~dlgDeclaracionEntrada();

private slots:

    void aceptar();

    void anadirInfraccion();
    void anadirPena();

    void recibirInfraccion(Infraccion infraccion);
    void recibirPena(Pena pena);

signals:

    void aceptarDeclaracion(Declaracion declaracion);

private:
    Ui::dlgDeclaracionEntrada *ui;

    Declaracion declaracion;

    Pena pena_estipulada;
    Infraccion infraccion_cometida;

    void cargarModelos();
};

#endif // DLGDECLARACIONENTRADA_H
