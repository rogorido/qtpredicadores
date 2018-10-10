#ifndef DLGNUEVACASA_H
#define DLGNUEVACASA_H

#include <QWidget>

#include "objs/lugar.h"
#include "objs/provincia.h"
#include "objs/variados.h"

class LugaresModel;
class CasasModel;
class QCompleter;
class QSqlQueryModel;
class QJsonObject;

class MyQmdiArea;

namespace Ui {
class dlgNuevaCasa;
}

class dlgNuevaCasa : public QWidget
{
    Q_OBJECT

public:
    explicit dlgNuevaCasa(QWidget *parent = 0, int casa = 0);
    ~dlgNuevaCasa();

private slots:

    void aceptarCasa();
    void anadirLugar();
    void quitarLugar(); // tenemos que quitarlo pq está en el struct
    void recibirLugar(Lugar lugar);
    void anadirFuente();

    void anadirProvincia();
    void quitarProvincia();
    void recibirProvincia(Provincia provincia);
    void recibirFuente(fuente f);

    void cerrar();

private:
    Ui::dlgNuevaCasa *ui;

    MyQmdiArea *mdiarea;

    LugaresModel *m_lugares;
    CasasModel *m_casas;

    struct elementopareado{
      int id = 0;
      QString elemento = "";
    };

    elementopareado lugar_struct;
    elementopareado provincia_struct;

    QSqlQueryModel *m_tipos;
    QCompleter *m_tipos_completer;
    QSqlQueryModel *m_advocaciones;
    QCompleter *m_advocaciones_completer;
    QSqlQueryModel *m_diocesis;
    QCompleter *m_diocesis_completer;

    /*
     * Aquí metemos los datos de si estamos modificando algo.
     */
    bool modificando = false;
    int casa_modificando = 0;

    /*
     * aquí metemos los datos que nos llegan de la source
     */
    QJsonObject *fuentedatos;
    /*
     * controlamos si hemos metido fuente
     */
    bool fuente_recibida = false;

    void borrarCampos();
    void cargarModelos();

    // cuando modificamos una...
    void cargarCasa();

};

#endif // DLGNUEVACASA_H
