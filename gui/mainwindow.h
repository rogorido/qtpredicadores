#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

class dlgNuevoCapitulo;
class dlgNuevaResolucion;
class dlgNuevaPersona;
class dlgNuevaCasa;
class dlgCapitulos;
class DlgResoluciones; // esto me he confundido y lo he puesto en mayúscula!
class dlgCiudades;
class dlgCasas;

class TemasModel;
class LugaresModel;
class PersonasModel;
class CasasModel;
class ProvinciasModel;
class CapitulosModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void nuevoCapitulo();
    void nuevaResolucion();
    void nuevaPersona();
    void nuevaCasa();
    void nuevaObra();
    void nuevaProvincia();
    void nuevoTema();

    void Capitulos();
    void Resoluciones();
    void Ciudades();
    void Casas();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    /* esto son formularios */
    dlgNuevoCapitulo *dlgCapitulo;
    dlgNuevaResolucion *dlgResolucion;
    dlgNuevaPersona *dlgPersona;
    dlgNuevaCasa *dlgCasa;

    // esto son los de gestión
    dlgCapitulos *FormCapitulos;
    DlgResoluciones *FormResoluciones;
    dlgCiudades *FormCiudades;
    dlgCasas *FormCasas;

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
