#ifndef DLGNUEVOCAPITULO_H
#define DLGNUEVOCAPITULO_H

#include <QDialog>

class QCompleter;
class QSqlQueryModel;

class LugaresModel;

namespace Ui {
class dlgNuevoCapitulo;
}

class dlgNuevoCapitulo : public QDialog
{
    Q_OBJECT

public:
    explicit dlgNuevoCapitulo(QWidget *parent = 0);
    ~dlgNuevoCapitulo();

private slots:
    void aceptarCapitulo();
    void fechaInicialCambiada();
    void fechaFinalCambiada();
    void anadirLugar();

private:
    Ui::dlgNuevoCapitulo *ui;

    QCompleter *lugar_completer;

    /* Esto sincermnete no se por que hay
     * que ponerlo asi aqui. Lo logico seria ponerlo
     * como variable local y luego pasarlo como referencia
     * al Qcompleter; pero no funciona... ¿sera porque se pierde
     * el modelo al salir?
     */
    QSqlQueryModel *lugar_query;

    /* pointers para los modelos de MainWindow */
    /* no me acordaba q esto hay que hacerlo así... */

    LugaresModel *m_lugares;

    /*
     * esto es una pequeña cutrada: lo uso para que solo si se ha
     * cambiado la fecha se meta, pq si no enteindo que mete la que viene
     * ya originalmente...
     */
    bool bFechaInicialModificada;
    bool bFechaFinalModificada;

    void cargarCompleters();

    int extraerLugar(QString lugar);

};

#endif // DLGNUEVOCAPITULO_H