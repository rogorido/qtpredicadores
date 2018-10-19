#ifndef DLGVIAJEENTRADA_H
#define DLGVIAJEENTRADA_H

#include <QWidget>

#include "src/objs/viaje.h"
#include "src/objs/lugar.h"
#include "src/objs/notas.h"

class QSqlQueryModel;
class QCompleter;

class MyQmdiArea;

namespace Ui {
class dlgViajeEntrada;
}

class dlgViajeEntrada : public QWidget
{
    Q_OBJECT

public:
    explicit dlgViajeEntrada(QWidget *parent = 0);
    ~dlgViajeEntrada();

signals:

    void emitirViaje(Viaje viaje);

private slots:

    void aceptarViaje();
    void anadirOrigen();
    void anadirDestino();
    void anadirMotivo();
    void quitarMotivo();

    void recibirLugar(Lugar lugar);
    void recibirDestino(Lugar lugar);

    void cerrar();

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::dlgViajeEntrada *ui;
    MyQmdiArea *mdiarea;

    QSqlQueryModel *motivos_model;
    QCompleter *motivos_completer;
    QSqlQueryModel *motivos_muerte_model;
    QCompleter *motivos_muerte_completer;
    QSqlQueryModel *lugares_muerte_model;
    QCompleter *lugares_muerte_completer;

    QStringList motivos;

    int lugar_origen_id = 0;
    int lugar_destino_id = 0;

    void cargarModelos();
};

#endif // DLGVIAJEENTRADA_H
