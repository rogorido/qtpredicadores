#ifndef DLGAFILIACIONENTRADA_H
#define DLGAFILIACIONENTRADA_H

#include <QDialog>

#include <objs/afiliacion.h>
#include "objs/persona.h"
#include "objs/casa.h"
#include "objs/provincia.h"
#include "objs/variados.h"

#include "models/afiliacionestablemodel.h"

class MyQmdiArea;

namespace Ui {
class dlgAfiliacionEntrada;
}

class dlgAfiliacionEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgAfiliacionEntrada(QWidget *parent = 0);
    ~dlgAfiliacionEntrada();

signals:

    void aceptarDatos(QList<Afiliacion*> listaafiliciones);

private slots:
    void anadirAfiliacion();
    void quitarAfiliacion();
    void aceptarAfiliaciones();
    void anadirPersona();
    void anadirCasaOrigen();
    void anadirCasaDestino();
    void anadirProvinciaOrigen();
    void anadirProvinciaDestino();

    void actualizarPersona(Persona persona);
    void actualizarCasaOrigen(Casa casa);
    void actualizarCasaDestino(Casa casa);
    void actualizarProvinciaOrigen(Provincia provincia);
    void actualizarProvinciaDestino(Provincia provincia);

    void cerrar();

private:
    Ui::dlgAfiliacionEntrada *ui;
    MyQmdiArea *mdiarea;

    AfiliacionesTableModel *afiliaciones_model;

    /*
     * lo hago pointer pq luego necesito borrarla
     * para crear una nueva... pero esto sinceramente no sé
     * si está muy bien así. Al hacerlo pointer esto tb
     * me cambia internamente lo de AprobacionesTableModel
     */
    Afiliacion *afiliacion_activa;
};

#endif // DLGAFILIACIONENTRADA_H
