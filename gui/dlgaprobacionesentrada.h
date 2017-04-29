#ifndef DLGAPROBACIONESENTRADA_H
#define DLGAPROBACIONESENTRADA_H

#include <QDialog>

#include "objs/aprobacion.h"
#include "objs/persona.h"
#include "objs/provincia.h"
#include "objs/variados.h"

#include "models/aprobacionestablemodel.h"

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

    void aceptarDatos(QList<Aprobacion> listaaprobaciones);

private slots:
    void anadirAprobacion();
    void aceptarAprobaciones();
    void anadirPersona();
    void anadirProvincia();

    void actualizarPersona(Persona persona);
    void actualizarProvincia(Provincia provincia);

private:
    Ui::dlgAprobacionesEntrada *ui;
    AprobacionesTableModel *aprobaciones_model;

    Aprobacion *aprobacion_activa;
};

#endif // DLGAPROBACIONESENTRADA_H
