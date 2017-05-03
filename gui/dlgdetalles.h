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

class JsonGestor;
class QSqlQueryModel;
class QCompleter;

namespace Ui {
class dlgDetalles;
}

class dlgDetalles : public QDialog
{
    Q_OBJECT

public:
    explicit dlgDetalles(JsonGestor *json, int t, QWidget *parent = 0);
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
    void actualizarCompleterValues(); // cuando cambia el campo key de json libre

    void on_btPersona_clicked();
    void on_btLugar_clicked();
    void on_btProvincia_clicked();
    void on_btJsonAnadirLibre_clicked();
    void on_btJsonAnadirDescripcion_clicked();
    void on_btModificarDetalles_toggled(bool checked);
    void on_btAnadirInteresante_clicked();
    void on_btAprobaciones_clicked();
    void on_btLicencias_clicked();
    void on_btPenas_clicked();
    void on_btCasa_clicked();
    void on_btAfiliaciones_clicked();
    void on_btOrdenanzas_clicked();

private:
    Ui::dlgDetalles *ui;

    /* estos son modelos solo de este form */
    QSqlQueryModel *m_keys;
    QSqlQueryModel *m_values;

    QCompleter *keys_completer;
    QCompleter *values_completer;

    JsonGestor *jsondetalles;

    void cargarModelos();
    void anadirExtraInfos(ExtraInfos extras);

    /*
     * el tipo sirve para escoger los valores del completer
     * para meter valores libres
     */

    int tipo;
};

#endif // DLGDETALLES_H
