#ifndef NUEVARESOLUCION_H
#define NUEVARESOLUCION_H

#include <QDialog>
#include <QMap>
#include <QJsonObject>

class TemasModel;
class LugaresModel;
class CasasModel;
class PersonasModel;

class QTreeWidgetItem;
class QSqlQueryModel;
class QCompleter;

namespace Ui {
class NuevaResolucion;
}

class NuevaResolucion : public QDialog
{
    Q_OBJECT

public:
    explicit NuevaResolucion(TemasModel *temas,
                             LugaresModel *lugares,
                             PersonasModel *personas,
                             CasasModel *casas,
                             int capitulo,
                             QWidget *parent = 0);
    ~NuevaResolucion();

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

private:
    Ui::NuevaResolucion *ui;

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

    /*
     * esto no sé si es una chapuza, pero por ahora funciona.
     * metemos en esta variable el item del treeDetalles
     * debajo del cual hay que ir metiendo children
     * que serían los datos concretos del json
     */
    QTreeWidgetItem *nivelactivo;

    struct elementopareado{
      int id;
      QString elemento;
    };

    QList<elementopareado> temas_lista;

    /*
     * QVariantMap es realmente un sinónimo de:
     * QMap<QString, QVariant>
     * La idea es meter los datos temporalmente en jsondetalles
     * y cuando ya esté listo se meten en jsondetalles_lista
     */
    //QVariantMap jsondetalles;
    /*
     * al final uso QMultiMap pq permite que haya varios
     * values por key, pues el peligro es que quiera meter
     * pej varios lugares en el json
     * PERO: aunque postgresql los reconoce, no funciona luego
     * con las funciones para sacar los datos!
     */
    //QMultiMap<QString, QVariant> jsondetalles;

    /*
     * al final uso QJsonObject. PERO: hay que tener en cuenta
     * que no permite repetir keys!
     */
    QJsonObject jsondetalles;
    QList<QJsonObject> jsondetalles_lista;

    void rellenarCombos();
    void cargarModelos();
    void introducirJson(const int id);
    void introducirTemas(const int id);
    void anadirTreeChildItem(const QString key, const QString value); // los elms del json van como children del QTreeWidget

    /*
     * esto se usa cuando abrimos el formulario
     * desde el formulario de capítulo
     */
    int capitulo_origen;
    bool origen;
};

#endif // NUEVARESOLUCION_H
