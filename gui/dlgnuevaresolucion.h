#ifndef DLGNUEVARESOLUCION_H
#define DLGNUEVARESOLUCION_H

#include <QDialog>
#include <QMap>
#include <QJsonObject>

class TemasModel;
class LugaresModel;
class CasasModel;
class PersonasModel;
class JsonGestor;

class dlgDetalles;

class QSqlQueryModel;
class QCompleter;

namespace Ui {
class dlgNuevaResolucion;
}

class dlgNuevaResolucion : public QDialog
{
    Q_OBJECT

public:
    explicit dlgNuevaResolucion(int capitulo,
                             QWidget *parent = 0);
    ~dlgNuevaResolucion();

private slots:

    void on_btNuevoTema_clicked();
    void on_btAnadirTema_clicked();
    void on_btQuitarTema_clicked();
    void on_btJsonAnadirDescripcion_clicked();
    void on_btJsonAnadirPersona_clicked();
    void on_btJsonAnadirCasa_clicked();
    void on_btJsonAnadirLibre_clicked();
    void on_btNuevoLugar_clicked();
    void on_btNuevaPersona_clicked();
    void on_btNuevaCasa_clicked();

    void nuevoJson();
    void aceptarResolucion(); // btOK

    void on_btBorrarElemento_clicked();

    void on_btModificarDetalles_toggled(bool checked);

    void on_btDetalles_clicked();

private:
    Ui::dlgNuevaResolucion *ui;

    dlgDetalles *dlgdetalles;

    /* pointers para los modelos de MainWindow */
    /* no me acordaba q esto hay que hacerlo así... */

    TemasModel *m_temas;
    LugaresModel *m_lugares;
    PersonasModel *m_personas;
    CasasModel *m_casas;

    JsonGestor *jsongestor;

    struct elementopareado{
      int id;
      QString elemento;
    };

    QList<elementopareado> temas_lista;

    void rellenarCombos();
    void introducirJson(const int id);
    void introducirTemas(const int id);

    /*
     * esto se usa cuando abrimos el formulario
     * desde el formulario de capítulo
     */
    int capitulo_origen;
    bool origen;
};

#endif // DLGNUEVARESOLUCION_H
