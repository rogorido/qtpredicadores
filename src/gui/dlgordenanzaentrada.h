#ifndef DLGORDENANZAENTRADA_H
#define DLGORDENANZAENTRADA_H

#include <QWidget>

#include "src/objs/ordenanza.h"
#include "src/objs/variados.h"
#include "src/objs/pena.h"
#include "src/objs/retroreferencia.h"

class QSqlQueryModel;
class QCompleter;
class dlgTemas;

class MyQmdiArea;

namespace Ui {
class dlgOrdenanzaEntrada;
}

class dlgOrdenanzaEntrada : public QWidget
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

    void on_btTemas_clicked();
    void cerrar();

signals:

    void aceptarOrdenanza(Ordenanza ordenanza);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::dlgOrdenanzaEntrada *ui;
    MyQmdiArea *mdiarea;

    dlgTemas *dlgtemas;

    QStringList lista_receptores;
    QStringList lista_objetos;
    Pena pena_estipulada;

    QSqlQueryModel *receptores_model;
    QCompleter *receptores_completer;
    QSqlQueryModel *objetos_model;
    QCompleter *objetos_completer;

    QList<elementopareado> temas_lista;

    Ordenanza ordenanza;

    void cargarModelos();

};

#endif // DLGORDENANZAENTRADA_H
