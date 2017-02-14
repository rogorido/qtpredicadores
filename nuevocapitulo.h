#ifndef NUEVOCAPITULO_H
#define NUEVOCAPITULO_H

#include <QDialog>

class QCompleter;
class QSqlQueryModel;

namespace Ui {
class NuevoCapitulo;
}

class NuevoCapitulo : public QDialog
{
    Q_OBJECT

public:
    explicit NuevoCapitulo(QWidget *parent = 0);
    ~NuevoCapitulo();

private slots:
    void aceptarCapitulo();
    void fechaCambiada();

private:
    Ui::NuevoCapitulo *ui;

    QCompleter *lugar_completer;

    /* Esto sincermnete no se por que hay
     * que ponerlo asi aqui. Lo logico seria ponerlo
     * como variable local y luego pasarlo como referencia
     * al Qcompleter; pero no funciona... ¿sera porque se pierde
     * el modelo al salir?
     */
    QSqlQueryModel *lugar_query;

    /*
     * esto es una pequeña cutrada: lo uso para que solo si se ha
     * cambiado la fecha se meta, pq si no enteindo que mete la que viene
     * ya originalmente...
     */
    bool bDateChanged;

    void cargarCompleters();

    int extraerLugar(QString lugar);



};

#endif // NUEVOCAPITULO_H
