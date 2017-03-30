#ifndef DLGNUEVARESOLUCION_H
#define DLGNUEVARESOLUCION_H

#include <QDialog>
#include "objs/provincia.h"

class TemasModel;
class ResolucionesModel;
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

    ResolucionesModel *m_resoluciones;

    struct elementopareado{
      int id;
      QString elemento;
    };

    QList<elementopareado> temas_lista;

    /*
     * si escogemos provincia lo metemos aquí
     * lo hacemos un pointer pq así luego se puede asignar
     * el valor NULL
     * Olvídalo!
     */
    int provincia_id;

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

    void anadirProvincia();
    void quitarProvincia();

    // en teoría casi un qlist de ints sería suficiente...
    void recibirTemas(QList<elementopareado> temas);
    void recibirProvincia(Provincia provincia);

};

#endif // DLGNUEVARESOLUCION_H
