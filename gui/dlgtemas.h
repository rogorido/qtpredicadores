#ifndef DLGTEMAS_H
#define DLGTEMAS_H

#include <QDialog>

#include "objs/tema.h"
#include "gui/dlgseleccionargeneral.h"

namespace Ui {
class dlgTemas;
}

class dlgTemas : public QDialog
{
    Q_OBJECT

public:
    explicit dlgTemas(QList<elementopareado> *temas_lista, QWidget *parent = 0);
    ~dlgTemas();

private slots:

    void on_btAnadirTema_clicked();
    void on_btQuitarTema_clicked();

    void recibirTema(Tema tema);

    //void aceptarTemas();

private:
    Ui::dlgTemas *ui;

    dlgSeleccionarGeneral *dlgseleccionar;

    QList<elementopareado> *temas;

signals:
    /*
     * curioso: esto tiene que ir después del bloque private:
     * pq si no da un error por el elementopareado
     */
    void temasSeleccionadosSignal(QList<elementopareado> temas);

};

#endif // DLGTEMAS_H
