#ifndef DECLARACIONENTRADA_H
#define DECLARACIONENTRADA_H

#include <QDialog>

#include "objs/variados.h"
#include "objs/pena.h"
#include "objs/infraccion.h"
#include "objs/declaracion.h"

namespace Ui {
class DeclaracionEntrada;
}

class DeclaracionEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit DeclaracionEntrada(QWidget *parent = 0);
    ~DeclaracionEntrada();

private slots:

    void aceptar();

    void anadirInfraccion();
    void anadirPena();

    void recibirInfraccion(Infraccion infraccion);
    void recibirPena(Pena pena);

signals:

    void aceptarDeclaracion(Declaracion declaracion);

private:
    Ui::DeclaracionEntrada *ui;
};

#endif // DECLARACIONENTRADA_H
