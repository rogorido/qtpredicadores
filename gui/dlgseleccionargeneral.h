#ifndef DLGSELECCIONARGENERAL_H
#define DLGSELECCIONARGENERAL_H

#include <QDialog>
#include "objs/variados.h"
#include "objs/persona.h"
#include "objs/lugar.h"
#include "objs/provincia.h"

class CasasModel;
class PersonasModel;
class LugaresModel;
class ProvinciasModel;
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
    void casaEscogidaSignal(int id, QString nombres);
    void personaEscogidaSignal(Persona autor);
    void lugarEscogidoSignal(Lugar lugar);
    void provinciaEscogidaSignal(Provincia provincia);

private:
    Ui::dlgSeleccionarGeneral *ui;

    QSqlTableModel *m_objeto;
    ProxyNombres *m_objeto_proxy;

    CasasModel *m_casas;
    LugaresModel *m_lugares;
    PersonasModel *m_personas;
    ProvinciasModel *m_provincias;

    void cargarModelo();
    void cargarTipo();

    // esto es un poco absurdo, tiene que haber otra manera...
    // pq esto lo q hace es llamar a las signals...
    void casa();
    void provincia();
    void persona();
    void lugar();

    tiposeleccionar tipo_seleccionado;

};

#endif // DLGSELECCIONARGENERAL_H
