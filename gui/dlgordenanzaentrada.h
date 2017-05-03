#ifndef DLGORDENANZAENTRADA_H
#define DLGORDENANZAENTRADA_H

#include <QDialog>

#include "objs/ordenanza.h"
#include "objs/variados.h"

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

signals:

    void aceptarOrdenanza(Ordenanza ordenanza);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::dlgOrdenanzaEntrada *ui;

    QStringList lista_receptores;
    QStringList lista_objetos;
};

#endif // DLGORDENANZAENTRADA_H
