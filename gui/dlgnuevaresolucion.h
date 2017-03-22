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

private:
    Ui::dlgNuevaResolucion *ui;

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

private slots:

    void on_btDetalles_clicked();
    void on_btTemas_clicked();

    void aceptarResolucion(); // btOK

    // en teoría casi un qlist de ints sería suficiente...
    void recibirTemas(QList<elementopareado> temas);

};

#endif // DLGNUEVARESOLUCION_H
