#ifndef DLGTEMAS_H
#define DLGTEMAS_H

#include <QWidget>

#include "src/objs/tema.h"
#include "dlgseleccionargeneral.h"

class MyQmdiArea;

namespace Ui {
class dlgTemas;
}

class dlgTemas : public QWidget
{
    Q_OBJECT

public:
    explicit dlgTemas(QList<elementopareado> *temas_lista, QWidget *parent = 0);
    ~dlgTemas();

private slots:

    void on_btAnadirTema_clicked();
    void on_btQuitarTema_clicked();

    void recibirTema(Tema tema);

    void cerrar();

    //void aceptarTemas();

private:
    Ui::dlgTemas *ui;
    MyQmdiArea *mdiarea;

    dlgSeleccionarGeneral *dlgseleccionar;

    QList<elementopareado> *temas;

    void meterTemaWidget(QString tema);

    /*
     * cuando volvermos a abrir el form y habíamos añadido
     * ya temas es necesario q ue los meta en la tabla
     */
    void inicializarTemasWidget();

signals:
    /*
     * curioso: esto tiene que ir después del bloque private:
     * pq si no da un error por el elementopareado
     */
    void temasSeleccionadosSignal(QList<elementopareado> temas);

};

#endif // DLGTEMAS_H
