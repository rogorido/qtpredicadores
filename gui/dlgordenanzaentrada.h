#ifndef DLGORDENANZAENTRADA_H
#define DLGORDENANZAENTRADA_H

#include <QDialog>

#include "objs/ordenanza.h"
#include "objs/variados.h"
#include "objs/pena.h"
#include "objs/retroreferencia.h"

class QSqlQueryModel;
class QCompleter;

namespace Ui {
class dlgOrdenanzaEntrada;
}

class dlgOrdenanzaEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgOrdenanzaEntrada(QWidget *parent = 0);
    ~dlgOrdenanzaEntrada();

private slots:

    void aceptar();

    void anadirObjeto();
    void anadirReceptor();
    void quitarObjeto();
    void quitarReceptor();
    void anadirPena();

    void recibirPena(Pena pena);

signals:

    void aceptarOrdenanza(Ordenanza ordenanza);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::dlgOrdenanzaEntrada *ui;

    QStringList lista_receptores;
    QStringList lista_objetos;
    Pena pena_estipulada;

    QSqlQueryModel *receptores_model;
    QCompleter *receptores_completer;
    QSqlQueryModel *objetos_model;
    QCompleter *objetos_completer;

    Ordenanza ordenanza;

    void cargarModelos();

};

#endif // DLGORDENANZAENTRADA_H
