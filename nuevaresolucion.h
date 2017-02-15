#ifndef NUEVARESOLUCION_H
#define NUEVARESOLUCION_H

#include <QDialog>

class Temas;

namespace Ui {
class NuevaResolucion;
}

class NuevaResolucion : public QDialog
{
    Q_OBJECT

public:
    explicit NuevaResolucion(Temas *temas, QWidget *parent = 0);
    ~NuevaResolucion();

private slots:

    void on_btNuevoTema_clicked();

private:
    Ui::NuevaResolucion *ui;

    /* pointers para los modelos de MainWindow */
    /* no me acordaba q esto hay que hacerlo así... */

    Temas *m_temas;

    void rellenarCombos();
};

#endif // NUEVARESOLUCION_H
