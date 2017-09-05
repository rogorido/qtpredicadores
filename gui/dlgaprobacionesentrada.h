#ifndef DLGAPROBACIONESENTRADA_H
#define DLGAPROBACIONESENTRADA_H

#include <QDialog>

#include "objs/aprobacion.h"
#include "objs/persona.h"
#include "objs/provincia.h"
#include "objs/variados.h"
#include "objs/casa.h"

#include "models/aprobacionestablemodel.h"

class MyQmdiArea;

namespace Ui {
class dlgAprobacionesEntrada;
}

class dlgAprobacionesEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgAprobacionesEntrada(QWidget *parent = 0);
    ~dlgAprobacionesEntrada();

signals:

    void aceptarDatos(QList<Aprobacion*> listaaprobaciones);

private slots:
    void anadirAprobacion();
    void quitarAprobacion();
    void aceptarAprobaciones();
    void anadirPersona();
    void anadirProvincia();
    void anadirCasa();

    void actualizarPersona(Persona persona);
    void actualizarProvincia(Provincia provincia);
    void actualizarCasa(Casa casa);

    void tabCambiado(int t);
    void cerrar();

private:
    Ui::dlgAprobacionesEntrada *ui;

    MyQmdiArea *mdiarea;

    AprobacionesTableModel *aprobaciones_model;

    /*
     * lo hago pointer pq luego necesito borrarla
     * para crear una nueva... pero esto sinceramente no sé
     * si está muy bien así. Al hacerlo pointer esto tb
     * me cambia internamente lo de AprobacionesTableModel
     */
    Aprobacion *aprobacion_activa;

    /*
     * esto realmente es un poco lío así... pero al tener dos
     * funcionalidades (lo de casas y personas) en el mismo formulario
     * lo voy a poner así. Luego en anadirAprobacion coge estos datos...
     */
    Persona persona_seleccionada;
    Provincia provincia_seleccionada;
    Casa casa_seleccionada;

    /*
     * guardamos aquí qué tab está seleccionado al cambiar
     * para saber si añadimos personas o instituciones.
     */
    int tabSeleccionado;
};

#endif // DLGAPROBACIONESENTRADA_H
