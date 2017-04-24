#ifndef DLGNUEVARESOLUCION_H
#define DLGNUEVARESOLUCION_H

#include <QDialog>
#include "objs/provincia.h"
#include "objs/capitulo.h"

class TemasModel;
class ResolucionesModel;
class JsonGestor;
class dlgDetalles;

class QSqlQueryModel;
class QCompleter;
class QStringListModel;

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
      int id = 0;
      QString elemento = "";
    };

    QList<elementopareado> temas_lista;

    /*
     * si escogemos provincia lo metemos aquí
     * lo hacemos un pointer pq así luego se puede asignar
     * el valor NULL
     * Olvídalo!
     */
    int provincia_id;
    int capitulo_id;
    QSqlQueryModel *m_epigrafe;
    QCompleter *m_epigrafe_completer;

    // para lo de los verbos y las expresiones
    QStringListModel *m_verbos;
    QStringListModel *m_expresiones;

    void cargarModelos();
    void rellenarCombos();
    void introducirJson(const int id);
    void introducirTemas(const int id);
    void borrarCampos();

    /*
     * esto se usa cuando abrimos el formulario
     * desde el formulario de capítulo
     */
    int capitulo_origen;
    bool origen;

private slots:

    void on_btDetalles_clicked();
    void on_btTemas_clicked();
    void on_btAnadirVerbo_clicked();
    void on_btQuitarVerbo_clicked();
    void on_btAnadirExpresion_clicked();
    void on_btQuitarExpresion_clicked();

    void aceptarResolucion(); // btOK

    void anadirProvincia();
    void quitarProvincia();

    void anadirCapitulo();
    void quitarCapitulo();

    // en teoría casi un qlist de ints sería suficiente...
    void recibirTemas(QList<elementopareado> temas);
    void recibirProvincia(Provincia provincia);
    void recibirCapitulo(Capitulo capitulo);

};

#endif // DLGNUEVARESOLUCION_H
