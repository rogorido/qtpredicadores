#ifndef DLGMASIVO_H
#define DLGMASIVO_H

#include <QDialog>

#include "objs/variados.h"

class QSqlTableModel;

namespace Ui {
class dlgMasivo;
}

class dlgMasivo : public QDialog
{
    Q_OBJECT

public:
    /*
     * el int chapter es cuando lo abrimos desde el formulario
     * de gestión de chapters.
     */
    explicit dlgMasivo(int chapter, QWidget *parent = 0);
    ~dlgMasivo();

private slots:

    void aceptar();
    void anadirProvincia();
    void quitarProvincia();

private:
    Ui::dlgMasivo *ui;

    QList<elementopareado> provinciasescogidas;

    /*
     * no uso el que ya tengo pq aquí cojo solo las columnas
     * que me interesan y así no tengo que estar ocultando
     * columnas en las views, que me aburre...
     * pero realmente es sensato?
     */
    QSqlTableModel *provincias;

    void desmarcarTodasProvincias();
    void cargarModelos();

    int chapterescogido;
};

#endif // DLGMASIVO_H
