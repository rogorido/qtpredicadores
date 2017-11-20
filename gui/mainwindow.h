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
class dlgNuevaMisionFilipinas;
class dlgNuevaFuente;
class dlgCapitulos;
class DlgResoluciones; // esto me he confundido y lo he puesto en mayúscula!
class dlgCiudades;
class dlgCasas;
class dlgEstadisticas;
class dlgReforma;
class dlgObispos;
class dlgMisiones;
class dlgDiocesis;

class dlgDetalles;

class TemasModel;
class LugaresModel;
class PersonasModel;
class CasasModel;
class ProvinciasModel;
class CapitulosModel;

class MyQmdiArea;

class QLabel;

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
    void nuevaMision();
    void nuevoTema();
    void nuevaFuente();
    void nuevaReforma(); // nombre un poco absurdo...

    void Capitulos();
    void Resoluciones();
    void Ciudades();
    void Casas();
    void Misiones();
    void Diocesis();

    void Estadisticas();

    void on_actionObispos_triggered();
    void updateStatusBarDerecha(QString mensaje);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    MyQmdiArea *mdiArea;
    QLabel *info_statusbar;

    /* esto son formularios */
    dlgNuevoCapitulo *dlgCapitulo;
    dlgNuevaResolucion *dlgResolucion;
    dlgNuevaPersona *dlgPersona;
    dlgNuevaCasa *dlgCasa;
    dlgNuevaDiocesis *dlgMeterNuevaDiocesis;
    dlgNuevoObispo *dlgObispo;
    dlgNuevaFuente *dlgFuente;
    dlgNuevaMisionFilipinas *dlgNuevaMision;
    dlgReforma *dlgReformaConvento;

    // esto son los de gestión
    dlgCapitulos *FormCapitulos;
    DlgResoluciones *FormResoluciones;
    dlgCiudades *FormCiudades;
    dlgCasas *FormCasas;
    dlgObispos *FormObispos;
    dlgMisiones *FormMisiones;
    dlgDiocesis *FormDiocesis;

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
