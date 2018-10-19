#ifndef DLGLICENCIAENTRADA_H
#define DLGLICENCIAENTRADA_H

#include <QDialog>
#include "src/objs/licencia.h"
#include "src/objs/casa.h"
#include "src/objs/provincia.h"

class QSqlQueryModel;
class QCompleter;

class MyQmdiArea;

namespace Ui {
class dlgLicenciaEntrada;
}

class dlgLicenciaEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgLicenciaEntrada(QWidget *parent = 0);
    ~dlgLicenciaEntrada();

private slots:

    void aceptar();
    void anadirReceptor();
    void quitarReceptor();
    void anadirOtorgante();
    void quitarOtorgante();
    void anadirProvincia();
    void anadirCasa();

    void recibirCasa(Casa casa);
    void recibirProvincia(Provincia provincia);

    void cerrar();

signals:

    void aceptarLicencia(Licencia licencia);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::dlgLicenciaEntrada *ui;
    MyQmdiArea *mdiarea;

    QStringList receptores;
    QStringList otorgantes;

    QSqlQueryModel *tipos_model;
    QCompleter *tipos_completer;
    QSqlQueryModel *otorgantes_model;
    QCompleter *otorgantes_completer;
    QSqlQueryModel *receptores_model;
    QCompleter *receptores_completer;
    QSqlQueryModel *asuntos_model;
    QCompleter *asuntos_completer;

    Licencia licencia_activa;

    int provincia_seleccionada = 0;
    int casa_seleccionada = 0;

    void cargarModelos();
};

#endif // DLGLICENCIAENTRADA_H
