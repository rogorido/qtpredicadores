#ifndef DLGSELECCIONARGENERAL_H
#define DLGSELECCIONARGENERAL_H

#include <QDialog>
#include "objs/variados.h"
#include "objs/persona.h"
#include "objs/lugar.h"

class CasasModel;
class PersonasModel;
class LugaresModel;
class QSqlTableModel;
class ProxyNombres;

namespace Ui {
class dlgSeleccionarGeneral;
}

class dlgSeleccionarGeneral : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSeleccionarGeneral(tiposeleccionar valor, QWidget *parent = 0);
    ~dlgSeleccionarGeneral();

private slots:

    void anadirObjeto();
    void actualizarFiltro(const QString filtro);
    void aceptar();

signals:
    void casaEscogida(int id, QString nombres);
    void personaEscogida(Persona autor);
    void lugarEscogido(Lugar lugar);

private:
    Ui::dlgSeleccionarGeneral *ui;

    QSqlTableModel *m_nombres;
    ProxyNombres *m_nombres_proxy;

    CasasModel *m_casas;
    LugaresModel *m_lugares;
    PersonasModel *m_personas;

    void cargarModelo();


};

#endif // DLGSELECCIONARGENERAL_H
