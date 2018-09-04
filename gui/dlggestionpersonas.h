#ifndef DLGGESTIONPERSONAS_H
#define DLGGESTIONPERSONAS_H

#include <QWidget>

class QMenu;
class QAction;
class QModelIndex;
class QSqlQueryModel;

class dlgNuevaPersona;

class MyQmdiArea;

class PersonasModel;
class SqlFiltroGestor;
class ProxyNombres;
class QJsonModel;

namespace Ui {
class dlgGestionPersonas;
}

class dlgGestionPersonas : public QWidget
{
    Q_OBJECT

public:
    explicit dlgGestionPersonas(QWidget *parent = nullptr);
    ~dlgGestionPersonas();

    // esto es público porque lo accedemos desde el mainwindow...
    void contarTotal();

private slots:

    // GUI
    void on_ckObispos_stateChanged(int arg1);
    void on_ckAutores_stateChanged(int arg1);
    void on_btModificarPersona_clicked();
    void on_btResetearFiltros_clicked();

    void menuContextual(const QPoint &point);
    void actualizarFiltro(const QString filtro);

    void actualizarSql(const QString s);

    void modificarPersona();

    /*
     * esto realmetne recoge una señal de sqlFiltroGestor
     * y genera la señal para la mainwindow
     */
    void emitirSenalTotalPersonas();

    /*
     * Actualizar el modelo tras recibir la señal de dlgNuevaPersona
     * de que se ha actualizado una persona
     */
    void actualizarModeloTrasPersonaActualizada();

    // para emitir la señal de que se ha seleccionado una persona
    void seleccionarPersona(const QModelIndex &idx);

signals:

    void infoBarraInferior(QString info);
    void infoPersonaSeleccionada(QString info);
    void infoPersonaSeleccionadaBorrar(); // al salir borramos la statusbar

private:
    Ui::dlgGestionPersonas *ui;
    MyQmdiArea *mdiarea;

    PersonasModel *m_persons;

    SqlFiltroGestor *sql_gestor;

    QMenu *menuContexto;
    QAction *a_cambiarPersona;

    ProxyNombres *proxy_personas;

    /*
     * guardamos el SQL que está activo
     */
    QString sqlactivo;

    // person_id
    int person_id;

    // lo usamos para la barra
    int total_personas;
    int total_filtrado;

    // para ver los detalles abajo
    QJsonModel *json_detalles;

    // esto para modificar obras,... por qué carajo lo hago como pointer?
    dlgNuevaPersona *dlgPersonaAModificar;

    /*
     * TODO: para ver las obras. Realmente habría que cambiarlo
     * para usar ObrasModel, pero para eso hay que adaptar ObrasModel
     */
    QSqlQueryModel *m_works;
    // idem
    QSqlQueryModel *m_obispados;

    void cargarMenus();
    void cargarModelos();

    void actualizarObras(const int id);
    void actualizarObispados(const int id);
};

#endif // DLGGESTIONPERSONAS_H
