#ifndef DLGSUFRAGIOSENTRADA_H
#define DLGSUFRAGIOSENTRADA_H

#include <QDialog>

#include "objs/sufragio.h"

namespace Ui {
class dlgSufragiosEntrada;
}

class dlgSufragiosEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSufragiosEntrada(QWidget *parent = 0);
    ~dlgSufragiosEntrada();

protected:
    bool eventFilter(QObject *obj, QEvent *e);

signals:

    void emitirSufragio(Sufragio sufragio);

private slots:

    void aceptarSufragio();
    void anadirDestinatario();
    void quitarDestinatario();

private:
    Ui::dlgSufragiosEntrada *ui;

    QStringList destinatarios;
};

#endif // DLGSUFRAGIOSENTRADA_H
