#ifndef DLGSELECCIONARGENERAL_H
#define DLGSELECCIONARGENERAL_H

#include <QDialog>
#include "objs/variados.h"
#include "objs/casa.h"
#include "objs/persona.h"
#include "objs/lugar.h"
#include "objs/provincia.h"
#include "objs/capitulo.h"
#include "objs/tema.h"
#include "objs/diocesis.h"

class CasasModel;
class PersonasModel;
class LugaresModel;
class ProvinciasModel;
class CapitulosModel;
class TemasModel;
class DiocesisModel;

class QSqlTableModel;
class ProxyNombres;

class MyQmdiArea;

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

    void actualizarObjeto();

signals:
    void casaEscogidaSignal(Casa casa);
    void personaEscogidaSignal(Persona autor);
    void lugarEscogidoSignal(Lugar lugar);
    void provinciaEscogidaSignal(Provincia provincia);
    void capituloEscogidoSignal(Capitulo capitulo);
    void temaEscogidoSignal(Tema tema);
    void diocesisEscogidaSignal(Diocesis diocesis);

private:
    Ui::dlgSeleccionarGeneral *ui;

    MyQmdiArea *mdiarea;

    QSqlTableModel *m_objeto;
    ProxyNombres *m_objeto_proxy;

    CasasModel *m_casas;
    LugaresModel *m_lugares;
    PersonasModel *m_personas;
    ProvinciasModel *m_provincias;
    CapitulosModel *m_capitulos;
    TemasModel *m_temas;
    DiocesisModel *m_diocesis;

    void cargarModelo();
    void cargarTipo();
    void cargarTituloVentana();

    // esto es un poco absurdo, tiene que haber otra manera...
    // pq esto lo q hace es llamar a las signals...
    void casa();
    void provincia();
    void persona();
    void lugar();
    void capitulo();
    void tema();
    void diocesis();

    /*
     * solamente tenemos esto para temas
     * pq en los otros casos usamos un dlgNuevoX
     * pero para temas no lo tenemos sino que usamos un inputbox.
     */
    void anadirTema();

    /*
     * en teoría esto es para comprobar si el modelo está vacío
     * y entonces cerramos el formulario pq me da un crash...
     * PERO: creo q no funciona (y además, sospecho que el crash
     * no era por eso...).
     * FIXME: de hecho, solo lo uso una vez...
     */
    void comprobarVacio();

    tiposeleccionar tipo_seleccionado;

};

#endif // DLGSELECCIONARGENERAL_H
