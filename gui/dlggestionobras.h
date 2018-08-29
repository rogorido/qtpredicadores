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


    // esto es público porque lo accedemos desde el mainwindow...
    void contarTotal();

private slots:

    // GUI
    void on_rbManuscritos_clicked();
    void on_rbImpresos_clicked();
    void on_rbTodos_clicked();    
    void on_ckSinMateria_stateChanged(int arg1);

    void actualizarSql(QString s);

    /*
     * esto realmetne recoge una señal de sqlFiltroGestor
     * y genera la señal para la mainwindow
     */
    void emitirSenalTotalObras();

signals:

    void infoBarraInferior(QString info);

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

    // lo usamos para la barra
    int total_obras;
    int total_filtrado;

    void cargarMenus();
    void cargarModelos();

};

#endif // DLGGESTIONOBRAS_H
