#ifndef DLGDIOCESISDETALLES_H
#define DLGDIOCESISDETALLES_H

#include <QWidget>

class QSqlQueryModel;
class QCompleter;
class MyQmdiArea;

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

private:
    Ui::dlgDiocesisDetalles *ui;
    MyQmdiArea *mdiarea;


    // la diócesis que estamos introduciendo
    int dioc_id;

    /*
     * modelos para completar. Realmente para el wdExtra no hace falta
     * pues se le pasa un sql y los crea él mismo
     */
    QSqlQueryModel *senores_model;
    QCompleter *senores_completer;

    void cargarModelos();
    void borrarCampos();


};

#endif // DLGDIOCESISDETALLES_H
