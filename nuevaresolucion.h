#ifndef NUEVARESOLUCION_H
#define NUEVARESOLUCION_H

#include <QDialog>
#include <QMap>

class Temas;
class Lugares;

namespace Ui {
class NuevaResolucion;
}

class NuevaResolucion : public QDialog
{
    Q_OBJECT

public:
    explicit NuevaResolucion(Temas *temas, Lugares *lugares, QWidget *parent = 0);
    ~NuevaResolucion();

private slots:

    void on_btNuevoTema_clicked();
    void on_btAnadirTema_clicked();
    void on_btQuitarTema_clicked();
    void on_btJsonAnadirDescripcion_clicked();
    void on_btJsonAnadirLugar_clicked();

    void nuevoJson();
    void aceptarResolucion(); // btOK

private:
    Ui::NuevaResolucion *ui;

    /* pointers para los modelos de MainWindow */
    /* no me acordaba q esto hay que hacerlo así... */

    Temas *m_temas;
    Lugares *m_lugares;

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
     */
    QMultiMap<QString, QVariant> jsondetalles;
    QList<QMultiMap<QString, QVariant>> jsondetalles_lista;

    void rellenarCombos();
    void generarJson();
};

#endif // NUEVARESOLUCION_H
