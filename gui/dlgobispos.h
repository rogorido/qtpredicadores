#ifndef DLGOBISPOS_H
#define DLGOBISPOS_H

#include <QWidget>

class QMenu;
class QAction;
class QSqlQueryModel;
class QModelIndex;
class SqlFiltroGestor;

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
    void actualizarSql(QString s);

    void on_cbDiocesis_currentIndexChanged(int index);

private:
    Ui::dlgObispos *ui;

    QSqlQueryModel *obispos_model;
    QSqlQueryModel *diocesis_model;

    SqlFiltroGestor *sql_gestor;

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
