#ifndef DLGDECLARACIONENTRADA_H
#define DLGDECLARACIONENTRADA_H

#include <QDialog>

#include "objs/variados.h"
#include "objs/pena.h"
#include "objs/infraccion.h"
#include "objs/declaracion.h"

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

    void cargarModelos();
};

#endif // DLGDECLARACIONENTRADA_H
