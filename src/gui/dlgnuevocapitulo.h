#ifndef DLGNUEVOCAPITULO_H
#define DLGNUEVOCAPITULO_H

#include <QWidget>

#include "src/objs/persona.h"
#include "src/objs/lugar.h"
#include "src/objs/provincia.h"

class QCompleter;
class QSqlQueryModel;

class LugaresModel;
class CapitulosModel;

class MyQmdiArea;

namespace Ui {
class dlgNuevoCapitulo;
}

class dlgNuevoCapitulo : public QWidget
{
    Q_OBJECT

public:
    explicit dlgNuevoCapitulo(QWidget *parent = 0);
    ~dlgNuevoCapitulo();

private slots:
    void aceptarCapitulo();
    void fechaInicialCambiada();
    void fechaFinalCambiada();
    void quitarLugar();
    void anadirLugar();
    void actualizarLugar(Lugar lugar);
    void anadirMaestroGeneral();
    void recibirMaestroGeneral(Persona persona);
    void anadirProvincia();
    void recibirProvincia(Provincia provincia);

    void on_btQuitarMaestroGeneral_clicked();

    void cerrar();

private:
    Ui::dlgNuevoCapitulo *ui;

    MyQmdiArea *mdiarea;

    QCompleter *lugar_completer;

    /* Esto sincermnete no se por que hay
     * que ponerlo asi aqui. Lo logico seria ponerlo
     * como variable local y luego pasarlo como referencia
     * al Qcompleter; pero no funciona... ¿sera porque se pierde
     * el modelo al salir?
     */
    QSqlQueryModel *lugar_query;

    /* pointers para los modelos de MainWindow */
    /* no me acordaba q esto hay que hacerlo así... */

    LugaresModel *m_lugares;

    CapitulosModel *m_capitulos;

    /*
     * esto es una pequeña cutrada: lo uso para que solo si se ha
     * cambiado la fecha se meta, pq si no enteindo que mete la que viene
     * ya originalmente...
     */
    bool bFechaInicialModificada;
    bool bFechaFinalModificada;

    struct elementopareado{
      int id = 0;
      QString elemento = "";
    };

    elementopareado maestrogeneral_struct;
    elementopareado lugarescogido_struct;
    elementopareado provinciaescogida_struct;

    void cargarCompleters();
    void borrarCampos();

    int extraerLugar(QString lugar);

};

#endif // DLGNUEVOCAPITULO_H
