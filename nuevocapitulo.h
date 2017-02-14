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

    void cargarCompleters();



};

#endif // NUEVOCAPITULO_H
