#ifndef DLGGESTIONPERSONAS_H
#define DLGGESTIONPERSONAS_H

#include <QWidget>

class QMenu;
class QAction;
class QSqlQueryModel;
class QModelIndex;

class dlgNuevaPersona;

class MyQmdiArea;

class SqlFiltroGestor;
class ProxyNombres;

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

    void menuContextual(const QPoint &point);
    void actualizarFiltro(const QString filtro);

    void actualizarSql(QString s);

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

signals:

    void infoBarraInferior(QString info);

private:
    Ui::dlgGestionPersonas *ui;
    MyQmdiArea *mdiarea;

    QSqlQueryModel *m_persons;

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

    // esto para modificar obras,... por qué carajo lo hago como pointer?
    dlgNuevaPersona *dlgPersonaAModificar;

    void cargarMenus();
    void cargarModelos();

};

#endif // DLGGESTIONPERSONAS_H
