#ifndef DLGLICENCIAENTRADA_H
#define DLGLICENCIAENTRADA_H

#include <QDialog>
#include "objs/licencia.h"

class QSqlQueryModel;
class QCompleter;

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

    void cerrar();

signals:

    void aceptarLicencia(Licencia licencia);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::dlgLicenciaEntrada *ui;

    QStringList receptores;
    QStringList otorgantes;

    QSqlQueryModel *tipos_model;
    QCompleter *tipos_completer;
    QSqlQueryModel *otorgantes_model;
    QCompleter *otorgantes_completer;
    QSqlQueryModel *receptores_model;
    QCompleter *receptores_completer;

    Licencia licencia_activa;

    void cargarModelos();
};

#endif // DLGLICENCIAENTRADA_H
