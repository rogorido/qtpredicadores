#ifndef DLGNUEVOOBISPO_H
#define DLGNUEVOOBISPO_H

#include <QWidget>
#include <QJsonObject>

#include "objs/persona.h"
#include "objs/diocesis.h"
#include "objs/variados.h"
#include "gui/dlgdetalles.h"

class QSqlQueryModel;
class QCompleter;
class QJsonModel;

class MyQmdiArea;

namespace Ui {
class dlgNuevoObispo;
}

class dlgNuevoObispo : public QWidget
{
    Q_OBJECT

public:
    explicit dlgNuevoObispo(QWidget *parent = 0);
    ~dlgNuevoObispo();

private slots:

    void aceptarObispo();
    void anadirPersona();
    void anadirDiocesis();
    void anadirFuente();
    void anadirDetalles();

    void fechaInicioCambiada();
    void fechaFinalCambiada();

    void recibirPersona(Persona persona);
    void recibirDiocesis(Diocesis diocesis);
    void recibirFuente(fuente datoobra);

    void cerrar();

private:
    Ui::dlgNuevoObispo *ui;
    MyQmdiArea *mdiarea;

    QSqlQueryModel *m_papas;
    QCompleter *m_papas_completer;

    /*
     * esto son los que escogemos con los modelos, dialogs, etc.
     * y los metemos aquí con su id. Lo ponemos como 0 por el lío
     * ese de que luego lo quiero borrar, etc.
     */
    int persona_id = 0;
    int diocesis_id = 0;
    int papa_id = 0;

    /*
     * aquí metemos los datos que nos llegan de la source
     */
    QJsonObject *fuentedatos;

    /*
     * métodos y variables para gestionar los detalles
     */
    QJsonModel *json_detalles;
    dlgDetalles *dlgdetalles;

    /*
     * esto realmente hay que hacerlo con un ObisposModel...
     */
    void introducirJson(const int id);
    void introducirNotas(const int id);


    /*
     * joder: eto es para que no me meta pej 1800-01-01
     * cuando no cambio la fecha final... pero tiene que haber otra forma
     * de hacerlo!
     */
    bool fecha_inicio_cambiada = false;
    bool fecha_final_cambiada = false;
    bool fuente_recibida = false;

    void cargarModelos();
    void borrarCampos();
};

#endif // DLGNUEVOOBISPO_H
