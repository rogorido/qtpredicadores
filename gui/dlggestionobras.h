#ifndef DLGGESTIONOBRAS_H
#define DLGGESTIONOBRAS_H

#include <QWidget>

class QMenu;
class QAction;
class QSqlQueryModel;
class QModelIndex;

class SqlFiltroGestor;

namespace Ui {
class dlgGestionObras;
}

class dlgGestionObras : public QWidget
{
    Q_OBJECT

public:
    explicit dlgGestionObras(QWidget *parent = nullptr);
    ~dlgGestionObras();

private slots:

    // GUI
    void on_rbManuscritos_clicked();
    void on_rbImpresos_clicked();
    void on_rbTodos_clicked();    
    void on_ckSinMateria_stateChanged(int arg1);

    void actualizarSql(QString s);

private:
    Ui::dlgGestionObras *ui;

    QSqlQueryModel *works_model;

    SqlFiltroGestor *sql_gestor;

    QMenu *menuContexto;

    /*
     * guardamos el SQL que está activo
     */
    QString sqlactivo;

    // work_id
    int work_id;

    void cargarMenus();
    void cargarModelos();

};

#endif // DLGGESTIONOBRAS_H
