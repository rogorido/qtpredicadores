#ifndef DLGOBISPOS_H
#define DLGOBISPOS_H

#include <QWidget>

class QMenu;
class QAction;
class QSqlQueryModel;
class QPoint;
class QModelIndex;

class Obispo;

namespace Ui {
class dlgObispos;
}

class dlgObispos : public QWidget
{
    Q_OBJECT

public:
    explicit dlgObispos(QWidget *parent = 0);
    ~dlgObispos();

private slots:
    void on_ckVolverAMirar_toggled(bool checked);
    void mostrarCustomMenu(QPoint pos);
    void seleccionadoObispo(const QModelIndex &idx);

    void modificarDiocesis();
    void modificarPersona();

private:
    Ui::dlgObispos *ui;

    Obispo *obispo_activo;

    QSqlQueryModel *obispos_model;
    QMenu *menuContexto;

    /*
     * FIXME: esto es para el campo see_again
     * que no es el de meta_info...
     */
    QAction *marcarNoMirar;
    QAction *cambiarPersona;
    QAction *cambiarDiocesis;

    /*
     * guardamos el SQL que está activo
     */
    QString sqlactivo;

    /*
     * esta variable guarda si estamos viendo los que
     * hay que volver a mirar
     */
    bool volveramirar = false;

    // bishop_id
    int obispo_seleccionado;


    void cargarModelos();
    void cargarMenus();
};

#endif // DLGOBISPOS_H
