#ifndef DLGDECLARACIONGENERALENTRADA_H
#define DLGDECLARACIONGENERALENTRADA_H

#include <QWidget>

#include "src/objs/declaracion.h"
#include "src/objs/provincia.h"
#include "src/objs/variados.h"
#include "src/objs/retroreferencia.h"

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
    // esto lo metemos como lista de ids de las provincias
    QList<int> lista_provincias;

    QSqlQueryModel *cargos_model;
    QCompleter *cargos_completer;
    QSqlQueryModel *instituciones_model;
    QCompleter *instituciones_completer;

    Declaracion declaracion;

    void cargarModelos();

};

#endif // DLGDECLARACIONGENERALENTRADA_H
