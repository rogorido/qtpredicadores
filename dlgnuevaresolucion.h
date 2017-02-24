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
    void on_btJsonAnadirLugar_clicked();
    void on_btJsonAnadirPersona_clicked();
    void on_btJsonAnadirCasa_clicked();
    void on_btJsonAnadirLibre_clicked();
    void on_btNuevoLugar_clicked();
    void on_btNuevaPersona_clicked();
    void on_btNuevaCasa_clicked();

    void nuevoJson();
    void aceptarResolucion(); // btOK
    void actualizarCompleterValues(); // cuando cambia el campo key de json libre

    void on_btBorrarElemento_clicked();

    void on_btModificarDetalles_toggled(bool checked);

private:
    Ui::dlgNuevaResolucion *ui;

    /* pointers para los modelos de MainWindow */
    /* no me acordaba q esto hay que hacerlo así... */

    TemasModel *m_temas;
    LugaresModel *m_lugares;
    PersonasModel *m_personas;
    CasasModel *m_casas;

    /* estos son modelos solo de este form */
    QSqlQueryModel *m_keys;
    QSqlQueryModel *m_values;

    QCompleter *keys_completer;
    QCompleter *values_completer;

    JsonGestor *jsongestor;

    struct elementopareado{
      int id;
      QString elemento;
    };

    QList<elementopareado> temas_lista;

    void rellenarCombos();
    void cargarModelos();
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
