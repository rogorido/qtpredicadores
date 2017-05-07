#ifndef DLGORDENANZAENTRADA_H
#define DLGORDENANZAENTRADA_H

#include <QDialog>

#include "objs/ordenanza.h"
#include "objs/variados.h"
#include "objs/pena.h"
#include "objs/retroreferencia.h"

class QSqlQueryModel;
class QCompleter;
class dlgTemas;

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

    /*
     * con esto se controla que se ha metido una nota
     * y que por tanto hay que pedirle al widget nota
     * que envíe su contenido
     */
    void notaIntroducida();

signals:

    void aceptarOrdenanza(Ordenanza ordenanza);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::dlgOrdenanzaEntrada *ui;
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

    bool notaintroducida = false;

    void cargarModelos();

};

#endif // DLGORDENANZAENTRADA_H
