#ifndef DLGNUEVAOBRA_H
#define DLGNUEVAOBRA_H

#include <QWidget>

#include "src/objs/persona.h"
#include "src/objs/lugar.h"
#include "dlgtemas.h"
#include "dlgdetalles.h"

class LugaresModel;
class ObrasModel;
class QCompleter;
class QSqlQueryModel;
class QJsonModel;
class Obra;

class MyQmdiArea;

namespace Ui {
class dlgNuevaObra;
}

class dlgNuevaObra : public QWidget
{
    Q_OBJECT

public:
    explicit dlgNuevaObra(QWidget *parent = 0, int obra = 0);
    ~dlgNuevaObra();

signals:

    void introducidaObra();

private:
    Ui::dlgNuevaObra *ui;

    MyQmdiArea *mdiarea;

    QSqlQueryModel *m_lugaresoriginales;
    QSqlQueryModel *m_idiomas;
    QSqlQueryModel *m_editores;

    QCompleter *c_lugaresoriginales;
    QCompleter *c_idiomas;
    QCompleter *c_editor;

    LugaresModel *m_lugares;
    ObrasModel *m_obras;

    Persona *autorescogido; // ver abajo lo del elementopareado
    Lugar *lugarescogido;

    /*
     * sinceramente: la idea de usar esto es para aquellos casos
     * en los que borro la persona que he metido. Si lo hago con una Persona
     * sinceramente no sé cómo "vaciarla".
     */

    elementopareado autorescogido_struct;
    elementopareado lugarescogido_struct;

    /*
     * esto no se define como pointer, pq luego no sé cómo
     * inicializarlo y es obligatorio antes de poder usarlo.
     * Lo que hago luego es pasarle una referencia a dlgtemas
     */
    QList<elementopareado> temasescogidos;

    QJsonModel *json_detalles;

    dlgTemas *dlgtemas;
    dlgDetalles *dlgdetalles;

    bool modificando = false;
    int obra_modificando = 0;

    void cargarCompleters();
    void borrarCampos();
    void introducirJson(const int id);

    // cuando abrimos el form para modificiar una obra:
    void cargarObra();

    /*
     * hacemos dos métodos iguales para introducir
     * la obra en la BD... Esto supone repetir el código
     * en parte pero no se ocurre nada mejor
     */
    void introducirObraEnBD(Obra *obra); // nueva
    void introducirObraEnBD(Obra *obra, bool modificar); // modificando una existente

private slots:

    //void on_txtAutor_doubleclicked();
    void on_btSeleccionarAutor_clicked();
    void on_btIntroducirLugar_clicked();
    void on_btQuitarAutor_clicked();
    void on_btQuitarLugar_clicked();
    void on_btTemas_clicked();
    void on_btDetalles_clicked();
    void on_btOK_clicked();

    void actualizarPersona(Persona autor);
    void actualizarLugar(Lugar lugar);

    void introducirTemas(int id);

    void cargarUI();
    void cerrar();

};

#endif // DLGNUEVAOBRA_H
