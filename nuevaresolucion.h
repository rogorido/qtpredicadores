#ifndef NUEVARESOLUCION_H
#define NUEVARESOLUCION_H

#include <QDialog>
#include <QMap>

class Temas;

namespace Ui {
class NuevaResolucion;
}

class NuevaResolucion : public QDialog
{
    Q_OBJECT

public:
    explicit NuevaResolucion(Temas *temas, QWidget *parent = 0);
    ~NuevaResolucion();

private slots:

    void on_btNuevoTema_clicked();
    void on_btAnadirTema_clicked();
    void on_btQuitarTema_clicked();
    void on_btJsonAnadirDescripcion_clicked();
    void on_btJsonAnadirLugar_clicked();

private:
    Ui::NuevaResolucion *ui;

    /* pointers para los modelos de MainWindow */
    /* no me acordaba q esto hay que hacerlo así... */

    Temas *m_temas;

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
    QMap<QString, QVariant> jsondetalles;
    QList<QMap<QString, QVariant>> jsondetalles_lista;

    void rellenarCombos();
};

#endif // NUEVARESOLUCION_H
