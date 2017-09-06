#ifndef DLGDECLARACIONGENERALENTRADA_H
#define DLGDECLARACIONGENERALENTRADA_H

#include <QWidget>

#include "objs/declaracion.h"
#include "objs/provincia.h"
#include "objs/variados.h"
#include "objs/retroreferencia.h"

class QSqlQueryModel;
class QCompleter;

class MyQmdiArea;

namespace Ui {
class dlgDeclaracionGeneralEntrada;
}

class dlgDeclaracionGeneralEntrada : public QWidget
{
    Q_OBJECT

public:
    explicit dlgDeclaracionGeneralEntrada(QWidget *parent = 0);
    ~dlgDeclaracionGeneralEntrada();

private slots:

    void aceptar();

    void anadirCargo();
    void anadirInstitucion();
    void anadirProvincia();
    void quitarCargo();
    void quitarInstitucion();
    void quitarProvincia();

    void recibirProvincia(Provincia provincia);

    void cerrar();

signals:

    void aceptarDeclaracion(Declaracion declaracion);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::dlgDeclaracionGeneralEntrada *ui;
    MyQmdiArea *mdiarea;

    QStringList lista_cargos;
    QStringList lista_instituciones;
    QStringList lista_provincias;

    QSqlQueryModel *cargos_model;
    QCompleter *cargos_completer;
    QSqlQueryModel *instituciones_model;
    QCompleter *instituciones_completer;

    Declaracion declaracion;

    void cargarModelos();

};

#endif // DLGDECLARACIONGENERALENTRADA_H
