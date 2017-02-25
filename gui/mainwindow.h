#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

class dlgNuevoCapitulo;
class dlgNuevaResolucion;
class dlgNuevaPersona;
class dlgNuevaCasa;
class dlgCapitulos;

class TemasModel;
class LugaresModel;
class PersonasModel;
class CasasModel;
class ProvinciasModel;

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

    void Capitulos();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    /* esto son formularios */
    dlgNuevoCapitulo *dlgCapitulo;
    dlgNuevaResolucion *dlgResolucion;
    dlgNuevaPersona *dlgPersona;
    dlgNuevaCasa *dlgCasa;
    dlgCapitulos *FormCapitulos;

    TemasModel *m_temas;
    LugaresModel *m_lugares;
    PersonasModel *m_personas;
    CasasModel *m_casas;
    ProvinciasModel *m_provincias;

    void cargarConexiones();
    void cargarModelos();
    void cargarMenues();
};

#endif // MAINWINDOW_H
