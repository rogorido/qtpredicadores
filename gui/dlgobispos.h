#ifndef DLGOBISPOS_H
#define DLGOBISPOS_H

#include <QWidget>

class QMenu;
class QAction;
class QSqlQueryModel;
class QModelIndex;

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
    void seleccionarObispo(const QModelIndex &idx);
    void menuContextual(const QPoint &point);

    void on_pbActivar_clicked();

    void on_ckVolverAMirar_toggled(bool checked);

    void modificarDiocesis();
    void modificarPersona();

private:
    Ui::dlgObispos *ui;

    QSqlQueryModel *obispos_model;

    QMenu *menuContexto;

    /*
     * FIXME: esto es para el campo see_again
     * que no es el de meta_info...
     */
    QAction *cambiarPersona;
    QAction *cambiarDiocesis;

    /*
     * guardamos el SQL que está activo
     */
    QString sqlactivo;

    // bishop_id
    int obispo_seleccionado;

    void cargarMenus();
    void cargarModelos();

};

#endif // DLGOBISPOS_H
