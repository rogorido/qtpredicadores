#ifndef DLGNUEVADIOCESIS_H
#define DLGNUEVADIOCESIS_H

#include <QDialog>

#include "objs/diocesis.h"
#include "objs/lugar.h"

class DiocesisModel;

namespace Ui {
class dlgNuevaDiocesis;
}

class dlgNuevaDiocesis : public QDialog
{
    Q_OBJECT

public:
    explicit dlgNuevaDiocesis(QWidget *parent = 0);
    ~dlgNuevaDiocesis();

private slots:

    void aceptarDiocesis();
    void borrarCampos();

    void anadirLugar();
    void anadirArchiDiocesis();

    void recibirLugar(Lugar lugar);
    void recibirArchiDiocesis(Diocesis diocesis);

private:
    Ui::dlgNuevaDiocesis *ui;

    DiocesisModel *m_diocesis;

    /*
     * aquí metemos esos valores que vendrían del
     * formulario seleccionar.
     */

    int sufraganea = 0;
    int lugar = 0;
};

#endif // DLGNUEVADIOCESIS_H
