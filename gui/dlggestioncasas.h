#ifndef DLGGESTIONCASAS_H
#define DLGESTIONCASAS_H

#include <QWidget>

#include "objs/provincia.h"
#include "objs/variados.h"

class CasasModel;
class ProxyNombres;
class SqlFiltroGestor;
class dlgNuevaCasa;

class MyQmdiArea;

namespace Ui {
class dlgGestionCasas;
}

class dlgGestionCasas : public QWidget
{
    Q_OBJECT

public:
    explicit dlgGestionCasas(QWidget *parent = 0);
    ~dlgGestionCasas();

private slots:

    void actualizarFiltro(const QString filtro);

    // para emitir la señal de que se ha seleccionado una persona
    void seleccionarCasa(const QModelIndex &idx);

    void actualizarModeloTrasCasaIntroducida();

    void actualizarSql(QString s);
    void cerrar();

    void on_btModificar_clicked();
    void on_rbFemeninas_toggled(bool checked);
    void on_rbMasculinas_toggled(bool checked);
    void on_rbTodas_toggled(bool checked);
    void on_btAnadirProvincia_clicked();

    void recibirProvincia(const Provincia provincia);

private:
    Ui::dlgGestionCasas *ui;
    MyQmdiArea *mdiarea;

    CasasModel *m_casas;
    ProxyNombres *proxy_casas;

    SqlFiltroGestor *sql_gestor;

    QString sqlactivo;

    // esto para modificar obras,... por qué carajo lo hago como pointer?
    // realmente este form lo he ido copiando de otros anteriores...
    dlgNuevaCasa *dlgCasaAModificar;

    // para filtrar por provincias
    QList<elementopareado> provincias_escogidas;

    void cargarModelos();

    /*
     * Al añadir/quitar provincias, para que actualice el filtro
     */
    void generarSQLProvincias();
};

#endif // DLGESTIONCASAS_H
