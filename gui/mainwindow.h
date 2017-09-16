#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

class dlgNuevoCapitulo;
class dlgNuevaResolucion;
class dlgNuevaPersona;
class dlgNuevaCasa;
class dlgNuevaDiocesis;
class dlgNuevoObispo;
class dlgNuevaFuente;
class dlgCapitulos;
class DlgResoluciones; // esto me he confundido y lo he puesto en mayúscula!
class dlgCiudades;
class dlgCasas;
class dlgEstadisticas;
class dlgReforma;
class dlgObispos;

class dlgDetalles;

class TemasModel;
class LugaresModel;
class PersonasModel;
class CasasModel;
class ProvinciasModel;
class CapitulosModel;

class MyQmdiArea;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    // para lo de MDIarea

    void abrirDetalles(dlgDetalles *dlg);

private slots:

    void nuevoCapitulo();
    void nuevaResolucion();
    void nuevaPersona();
    void nuevaCasa();
    void nuevaObra();
    void nuevaProvincia();
    void nuevaDiocesis();
    void nuevoObispo();
    void nuevoTema();
    void nuevaFuente();
    void nuevaReforma(); // nombre un poco absurdo...

    void Capitulos();
    void Resoluciones();
    void Ciudades();
    void Casas();

    void Estadisticas();

    void on_actionObispos_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    MyQmdiArea *mdiArea;

    /* esto son formularios */
    dlgNuevoCapitulo *dlgCapitulo;
    dlgNuevaResolucion *dlgResolucion;
    dlgNuevaPersona *dlgPersona;
    dlgNuevaCasa *dlgCasa;
    dlgNuevaDiocesis *dlgDiocesis;
    dlgNuevoObispo *dlgObispo;
    dlgNuevaFuente *dlgFuente;
    dlgReforma *dlgReformaConvento;

    // esto son los de gestión
    dlgCapitulos *FormCapitulos;
    DlgResoluciones *FormResoluciones;
    dlgCiudades *FormCiudades;
    dlgCasas *FormCasas;
    dlgObispos *FormObispos;

    // esto es para gestionarlos con lo de MDIarea
    dlgDetalles *dlgdetalles;

    dlgEstadisticas *FormEstadisticas;

    TemasModel *m_temas;
    LugaresModel *m_lugares;
    PersonasModel *m_personas;
    CasasModel *m_casas;
    ProvinciasModel *m_provincias;
    CapitulosModel *m_capitulos;

    void cargarModelos();
    void cargarMenues();
};

#endif // MAINWINDOW_H
