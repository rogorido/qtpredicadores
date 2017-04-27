#ifndef DLGMASIVO_H
#define DLGMASIVO_H

#include <QDialog>

class JsonGestor;
class QSqlQueryModel;
class QSortFilterProxyModel;

namespace Ui {
class dlgMasivo;
}

class dlgMasivo : public QDialog
{
    Q_OBJECT

public:
    explicit dlgMasivo(JsonGestor *json, QWidget *parent = 0);
    ~dlgMasivo();

private slots:

    void aceptar();

private:
    Ui::dlgMasivo *ui;
    JsonGestor *jsondetalles;

    /*
     * no uso el que ya tengo pq aquí cojo solo las columnas
     * que me interesan y así no tengo que estar ocultando
     * columnas en las views, que me aburre...
     * pero realmente es sensato?
     */
    QSqlQueryModel *provincias;
    QSortFilterProxyModel *prov_escogidas;
    QSortFilterProxyModel *prov_noescogidas;

    void desmarcarTodasProvincias();
    void cargarModelos();
};

#endif // DLGMASIVO_H
