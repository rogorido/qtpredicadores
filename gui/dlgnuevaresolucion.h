#ifndef DLGNUEVARESOLUCION_H
#define DLGNUEVARESOLUCION_H

#include <QDialog>

class TemasModel;
class JsonGestor;
class dlgDetalles;

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
    void on_btDetalles_clicked();

    void aceptarResolucion(); // btOK

private:
    Ui::dlgNuevaResolucion *ui;

    TemasModel *m_temas;
    JsonGestor *jsongestor;
    dlgDetalles *dlgdetalles;

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
