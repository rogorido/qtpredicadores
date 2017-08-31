#ifndef DLGDETALLES_H
#define DLGDETALLES_H

#include <QDialog>

#include "objs/persona.h"
#include "objs/casa.h"
#include "objs/lugar.h"
#include "objs/provincia.h"
#include "objs/aprobacion.h"
#include "objs/licencia.h"
#include "objs/pena.h"
#include "objs/afiliacion.h"
#include "objs/ordenanza.h"
#include "objs/sufragio.h"
#include "objs/diocesis.h"
#include "objs/declaracion.h"

class QSqlQueryModel;
class QCompleter;
class QJsonModel;

namespace Ui {
class dlgDetalles;
}

class dlgDetalles : public QDialog
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
    void on_btBorrarJsonLibre_clicked();
    void on_btAnadirJsonLibre_clicked();
    void on_btBorrarBloqueJson_clicked();
    void on_btSufragios_clicked();
    void on_btTraslado_clicked();

    void anadirDatosLibres();
    void anadirInteresante();
    void actualizarCompleterValues(); // cuando cambia el campo key de json libre

    // para gestionar el qtreewidget
    void anadirChildItem(const QString &key, const QString &value);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::dlgDetalles *ui;

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
};

#endif // DLGDETALLES_H
