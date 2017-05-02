#ifndef DLGAFILIACIONENTRADA_H
#define DLGAFILIACIONENTRADA_H

#include <QDialog>

#include <objs/afiliacion.h>
#include "objs/persona.h"
#include "objs/provincia.h"
#include "objs/variados.h"

#include "models/afiliacionestablemodel.h"

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
    void anadirProvincia();

    void actualizarPersona(Persona persona);
    void actualizarProvincia(Provincia provincia);

private:
    Ui::dlgAfiliacionEntrada *ui;
    AfiliacionesTableModel *afiliaciones_model;

    /*
     * lo hago pointer pq luego necesito borrarla
     * para crear una nueva... pero esto sinceramente no sé
     * si está muy bien así. Al hacerlo pointer esto tb
     * me cambia internamente lo de AprobacionesTableModel
     */
    Afiliacion *aprobacion_activa;
};

#endif // DLGAFILIACIONENTRADA_H
