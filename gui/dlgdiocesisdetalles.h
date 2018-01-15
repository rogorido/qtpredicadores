#ifndef DLGDIOCESISDETALLES_H
#define DLGDIOCESISDETALLES_H

#include <QWidget>
#include <QJsonDocument>

class QSqlQueryModel;
class QCompleter;
class MyQmdiArea;

#include "objs/diocesis.h"

namespace Ui {
class dlgDiocesisDetalles;
}

class dlgDiocesisDetalles : public QWidget
{
    Q_OBJECT

public:
    explicit dlgDiocesisDetalles(int diocesis_id, QWidget *parent = 0);
    ~dlgDiocesisDetalles();

private slots:

    void aceptar();
    void cancelar();

    void AnadirArchiDiocesis();
    void recibirArchiDiocesis(Diocesis diocesis);

private:
    Ui::dlgDiocesisDetalles *ui;
    MyQmdiArea *mdiarea;


    // la diócesis que estamos introduciendo
    int dioc_id;

    /*
     * la metrópolis de la que estamos actualizando...
     * TODO: mierda qué pasa si ya lo tenemos metido?
     */
    int sufraganea_id = 0;

    /*
     * modelos para completar. Realmente para el wdExtra no hace falta
     * pues se le pasa un sql y los crea él mismo
     */
    QSqlQueryModel *m_senores;
    QCompleter *senores_completer;
    QSqlQueryModel *m_divisas;
    QCompleter *divisas_completer;

    void cargarModelos();
    void borrarCampos();

    /*
     * le pasamos un qjsondoc y lo metemos en la bd.
     * La razón de no hacerlo en aceptar es que así si tenemos que
     * no hay datos es más fácil...
     */
    void introducirDatos(QJsonDocument json_doc);


};

#endif // DLGDIOCESISDETALLES_H
