#ifndef DLGDETALLES_H
#define DLGDETALLES_H

#include <QWidget>

#include "src/objs/persona.h"
#include "src/objs/casa.h"
#include "src/objs/lugar.h"
#include "src/objs/provincia.h"
#include "src/objs/aprobacion.h"
#include "src/objs/licencia.h"
#include "src/objs/pena.h"
#include "src/objs/afiliacion.h"
#include "src/objs/ordenanza.h"
#include "src/objs/sufragio.h"
#include "src/objs/diocesis.h"
#include "src/objs/declaracion.h"
#include "src/objs/viaje.h"

class QSqlQueryModel;
class QCompleter;
class QJsonModel;
class QMenu;
class QAction;

class MyQmdiArea;

namespace Ui {
class dlgDetalles;
}

class dlgDetalles : public QWidget
{
    Q_OBJECT

public:
    explicit dlgDetalles(QJsonModel *json, int t, bool anadir, QWidget *parent = 0);
    ~dlgDetalles();

private slots:
    void recibirPersona(Persona persona);
    void recibirLugar(Lugar lugar);
    void recibirCasa(Casa casa);
    void recibirProvincia(Provincia provincia);
    void recibirAprobaciones(QList<Aprobacion*> lista_aprobaciones);
    void recibirLicencia(Licencia licencia);
    void recibirPena(Pena pena);
    void recibirAfiliacion(QList<Afiliacion*> lista_afiliaciones);
    void recibirOrdenanza(Ordenanza ordenanza);
    void recibirSufragio(Sufragio sufragio);
    void recibirTraslado(Diocesis diocesis);
    void recibirDeclaracion(Declaracion declaracion);
    void recibirViaje(Viaje viaje);
    void recibirReedicion(QJsonObject reedicion);

    // GUI
    void on_btPersona_clicked();
    void on_btLugar_clicked();
    void on_btProvincia_clicked();
    void on_btAprobaciones_clicked();
    void on_btLicencias_clicked();
    void on_btPenas_clicked();
    void on_btCasa_clicked();
    void on_btAfiliaciones_clicked();
    void on_btOrdenanzas_clicked();
    void on_btDeclaraciones_clicked();
    void on_btDeclaracionGeneral_clicked();
    void on_btViaje_clicked();
    void on_btBorrarJsonLibre_clicked();
    void on_btAnadirJsonLibre_clicked();
    void on_btBorrarBloqueJson_clicked();
    void on_btSufragios_clicked();
    void on_btTraslado_clicked();
    void on_btAdmoniciones_clicked(); // realmente es el mismo form que ordenanzas
    void on_btComisiones_clicked(); // realmente es el mismo form que ordenanzas    
    void on_pbExpandAll_clicked();
    void on_btReedicion_clicked();
    void on_btNacimiento_clicked();
    void on_btProfesion_clicked();
    void on_btBeato_clicked();
    void on_btVenerable_clicked();
    void on_btPater_clicked();

    void anadirDatosLibres();
    void anadirInteresante();
    void actualizarCompleterValues(); // cuando cambia el campo key de json libre

    // para gestionar el qtreewidget
    void anadirChildItem(const QString &key, const QString &value);

    void cerrar();
    void ocultar();

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::dlgDetalles *ui;

    QMenu *menu_declaraciones;
    QMenu *menu_ordenanzas;
    QAction *action_declaracion_general;
    QAction *action_declaraciones;

    QAction *action_ordenanzas;
    QAction *action_comisiones;
    QAction *action_prohibiciones;
    QAction *action_admoniciones;

    MyQmdiArea *mdiarea;

    /*
     * este es el model donde vamos metiendo QJsonObjects
     * y que se comunica con la view. Este model viene realmente
     * de otros formularios!
     */
    QJsonModel *json_model;

    /*
     * con esto podemos crear QJsonObjects "libres"
     * en el sentido de que voy metiendo los campos a mano.
     */
    QJsonObject json_libre;

    /* estos son modelos solo de este form */
    QSqlQueryModel *m_keys;
    QSqlQueryModel *m_values;

    QCompleter *keys_completer;
    QCompleter *values_completer;

    void cargarModelos();
    void cargarMenus();

    /*
     * el tipo sirve para escoger los valores del completer
     * para meter valores libres
     */

    int tipo;

    /*
     * esta variable controla si llamamos el form desde alguno
     * de los forms de gestión.
     */
    bool anadiendo;

    /*
     * controlamos si el TreeVeiw está expandida
     */
    bool expandido = false;
};

#endif // DLGDETALLES_H
