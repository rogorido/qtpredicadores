#ifndef DLGGESTIONOBRAS_H
#define DLGGESTIONOBRAS_H

#include <QWidget>

#include "objs/variados.h"
#include "objs/tema.h"

class QMenu;
class QAction;
class QSqlQueryModel;
class QModelIndex;

class dlgNuevaObra;

class MyQmdiArea;

class SqlFiltroGestor;

namespace Ui {
class dlgGestionObras;
}

class dlgGestionObras : public QWidget
{
    Q_OBJECT

public:
    explicit dlgGestionObras(QWidget *parent = 0);
    ~dlgGestionObras();

    // esto es público porque lo accedemos desde el mainwindow...
    void contarTotal();

private slots:

    // GUI
    void on_rbManuscritos_clicked();
    void on_rbImpresos_clicked();
    void on_rbTodos_clicked();    
    void on_ckSinMateria_stateChanged(int arg1);    
    void on_pbAnadirTema_clicked();
    void on_pbQuitarTema_clicked();
    void on_pbQuitarTemasTodos_clicked();

    void menuContextual(const QPoint &point);

    void actualizarSql(QString s);

    void modificarObra();
    void verPersona();
    void modificarPersona();

    /*
     * esto realmetne recoge una señal de sqlFiltroGestor
     * y genera la señal para la mainwindow
     */
    void emitirSenalTotalObras();

    /*
     * Actualizar el modelo tras recibir la señal de dlgNuevaObra
     * de que se ha actualizado una obra
     */
    void actualizarModeloTrasObraActualizada();

    void recibirTema(Tema tema);

signals:

    void infoBarraInferior(QString info);

private:
    Ui::dlgGestionObras *ui;
    MyQmdiArea *mdiarea;

    QSqlQueryModel *works_model;

    SqlFiltroGestor *sql_gestor;

    QMenu *menuContexto;
    QAction *a_verPersona;
    QAction *a_cambiarPersona;
    QAction *a_cambiarObra;

    /*
     * guardamos el SQL que está activo
     */
    QString sqlactivo;

    // work_id
    int work_id;

    // lo usamos para la barra
    int total_obras;
    int total_filtrado;

    // esto para modificar obras,... por qué carajo lo hago como pointer?
    dlgNuevaObra *dlgObraAModificar;

    // para filtrar por materias
    QList<elementopareado> materias_escogidas;

    void cargarMenus();
    void cargarModelos();

    void generarSQLMaterias();

};

#endif // DLGGESTIONOBRAS_H
