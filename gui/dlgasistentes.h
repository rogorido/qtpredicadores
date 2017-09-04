#ifndef DLGASISTENTES_H
#define DLGASISTENTES_H

#include <QDialog>

#include "objs/variados.h"

class QSqlTableModel;

namespace Ui {
class dlgAsistentes;
}

class dlgAsistentes : public QDialog
{
    Q_OBJECT

public:
    /*
     * el int chapter es cuando lo abrimos desde el formulario
     * de gestión de chapters.
     */
    explicit dlgAsistentes(int chapter, QWidget *parent = 0);
    ~dlgAsistentes();

private slots:

    void aceptar();
    void anadirProvincia();
    void quitarProvincia();

private:
    Ui::dlgAsistentes *ui;

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

#endif // DLGASISTENTES_H
