#ifndef DLGNUEVADIOCESIS_H
#define DLGNUEVADIOCESIS_H

#include <QWidget>

#include "objs/diocesis.h"
#include "objs/lugar.h"

class DiocesisModel;
class MyQmdiArea;
class QStringList;
class QCompleter;

namespace Ui {
class dlgNuevaDiocesis;
}

class dlgNuevaDiocesis : public QWidget
{
    Q_OBJECT

public:
    explicit dlgNuevaDiocesis(QWidget *parent = 0);
    ~dlgNuevaDiocesis();

private slots:

    void aceptarDiocesis();
    void borrarCampos();

    void anadirLugar();
    void anadirArchiDiocesis();

    void recibirLugar(Lugar lugarrecibido);
    void recibirArchiDiocesis(Diocesis diocesis);

    void cerrar();

private:
    Ui::dlgNuevaDiocesis *ui;
    MyQmdiArea *mdiarea;

    DiocesisModel *m_diocesis;

    /*
     * aquí metemos esos valores que vendrían del
     * formulario seleccionar.
     */

    int sufraganea = 0;
    int lugar = 0;

    /*
     * para meter lo de los motivos de desaparición
     */
    QStringList *lista_motivos;
    QCompleter *motivos_completer;

};

#endif // DLGNUEVADIOCESIS_H
