#ifndef DLGNUEVOOBISPO_H
#define DLGNUEVOOBISPO_H

#include <QDialog>
#include <QJsonObject>

#include "objs/persona.h"
#include "objs/diocesis.h"
#include "objs/variados.h"
#include "gui/dlgdetalles.h"

class QSqlQueryModel;
class QCompleter;
class QJsonModel;

namespace Ui {
class dlgNuevoObispo;
}

class dlgNuevoObispo : public QDialog
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

    void fechaInicioCambiada();
    void fechaFinalCambiada();

    void recibirPersona(Persona persona);
    void recibirDiocesis(Diocesis diocesis);
    void recibirFuente(fuente datoobra);

private:
    Ui::dlgNuevoObispo *ui;

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

    void introducirJson(const int id);


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