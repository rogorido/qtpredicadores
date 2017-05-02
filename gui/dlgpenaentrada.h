#ifndef DLGPENAENTRADA_H
#define DLGPENAENTRADA_H

#include <QDialog>

#include "objs/pena.h"

class QSqlQueryModel;
class QCompleter;

namespace Ui {
class dlgPenaEntrada;
}

class dlgPenaEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgPenaEntrada(QWidget *parent = 0);
    ~dlgPenaEntrada();

private slots:

    void aceptar();
    void anadirPenasTipos();
    void quitarPenasTipos();
    void anadirPenados();
    void quitarPenados();

signals:

    void aceptarPena(Pena pena);

private:
    Ui::dlgPenaEntrada *ui;

    QStringList penastipos;
    QStringList penados;

    QSqlQueryModel *tipos_model;
    QCompleter *tipos_completer;
    QSqlQueryModel *penados_model;
    QCompleter *penados_completer;
    QSqlQueryModel *penatexto_model;
    QCompleter *penatexto_completer;
    QSqlQueryModel *motivo_model;
    QCompleter *motivo_completer;

    Pena pena;

    void cargarModelos();
};

#endif // DLGPENAENTRADA_H
