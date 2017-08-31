#ifndef DLGINFRACCIONENTRADA_H
#define DLGINFRACCIONENTRADA_H

#include <QDialog>

#include "objs/variados.h"
#include "objs/infraccion.h"

namespace Ui {
class dlgInfraccionEntrada;
}

class dlgInfraccionEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgInfraccionEntrada(QWidget *parent = 0);
    ~dlgInfraccionEntrada();

private slots:

    void aceptar();

    void anadirInfractor();
    void quitarInfractor();

signals:

    void aceptarInfraccion(Infraccion infraccion);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::dlgInfraccionEntrada *ui;

    Infraccion infraccion;

    QStringList lista_infractores;

    void cargarModelos();
};

#endif // DLGINFRACCIONENTRADA_H
