#ifndef DLGORDENANZAENTRADA_H
#define DLGORDENANZAENTRADA_H

#include <QDialog>

#include "objs/ordenanza.h"

namespace Ui {
class dlgOrdenanzaEntrada;
}

class dlgOrdenanzaEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgOrdenanzaEntrada(QWidget *parent = 0);
    ~dlgOrdenanzaEntrada();

signals:

    void aceptarOrdenanza(Ordenanza ordenanza);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::dlgOrdenanzaEntrada *ui;
};

#endif // DLGORDENANZAENTRADA_H
