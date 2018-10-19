#ifndef DLGDECLARACIONENTRADA_H
#define DLGDECLARACIONENTRADA_H

#include <QDialog>

#include "src/objs/variados.h"
#include "src/objs/pena.h"
#include "src/objs/infraccion.h"
#include "src/objs/declaracion.h"

class QJsonModel;
class MyQmdiArea;

/*
 * Tengo el problema de que no sé cómo borrar una infracción o una pena
 * pq al ser un objeto no sé cómo borrarlo...
 * Tal vez habría que hacerlo en la clase con un reset o algo así...
 */

/*
 * TODO: en este formulario habría quehacer un sistmea para borrar lo que
 * ya he metido. Sospecho q tendría que hacer una QList o algo de ifnracciones
 * y gestionarlas... Así como está ahora creo q no se puede, no?
 * A no ser que reinicilice sin más el objeto infraccion_cometida...
 */

namespace Ui {
class dlgDeclaracionEntrada;
}

class dlgDeclaracionEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgDeclaracionEntrada(QWidget *parent = 0);
    ~dlgDeclaracionEntrada();

private slots:

    void aceptar();

    void anadirInfraccion();
    void anadirPena();

    void recibirInfraccion(Infraccion infraccion);
    void recibirPena(Pena pena);

    void cerrar();

signals:

    void aceptarDeclaracion(Declaracion declaracion);

private:
    Ui::dlgDeclaracionEntrada *ui;
    MyQmdiArea *mdiarea;

    Declaracion declaracion;


    /*
     * este es el model donde vamos metiendo QJsonObjects
     * y que se comunica con la view.
     */
    QJsonModel *json_model_infracciones;

    Pena pena_estipulada;
    Infraccion infraccion_cometida;

    void cargarModelos();
};

#endif // DLGDECLARACIONENTRADA_H
