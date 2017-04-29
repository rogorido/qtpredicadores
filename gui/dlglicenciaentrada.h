#ifndef DLGLICENCIAENTRADA_H
#define DLGLICENCIAENTRADA_H

#include <QDialog>

#include "objs/licencia.h"

namespace Ui {
class dlgLicenciaEntrada;
}

class dlgLicenciaEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgLicenciaEntrada(QWidget *parent = 0);
    ~dlgLicenciaEntrada();

public slots:

    void aceptar();
    void anadirReceptor();
    void quitarReceptor();
    void anadirOtorgante();
    void quitarOtorgante();

signals:

    void aceptarLicencia(Licencia licencia);

private:
    Ui::dlgLicenciaEntrada *ui;

    QStringList receptores;
    QStringList otorgantes;

    Licencia licencia_activa;

};

#endif // DLGLICENCIAENTRADA_H
