#ifndef DLGSUFRAGIOSENTRADA_H
#define DLGSUFRAGIOSENTRADA_H

#include <QDialog>

#include "objs/sufragio.h"

class QSqlQueryModel;
class QCompleter;

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

    void cerrar();

private:
    Ui::dlgSufragiosEntrada *ui;

    QSqlQueryModel *destinatarios_model;
    QCompleter *destinatarios_completer;
    QSqlQueryModel *motivos_model;
    QCompleter *motivos_completer;

    Sufragio sufragio;

    QStringList destinatarios;

    void cargarModelos();
};

#endif // DLGSUFRAGIOSENTRADA_H
