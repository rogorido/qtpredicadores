#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

class NuevoCapitulo;
class NuevaResolucion;
class dlgNuevaPersona;
class NuevaCasa;
class DlgCapitulos;

class TemasModel;
class LugaresModel;
class PersonasModel;
class CasasModel;

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
    NuevoCapitulo *Capitulo;
    NuevaResolucion *Resolucion;
    dlgNuevaPersona *Persona;
    NuevaCasa *Casa;
    DlgCapitulos *FormCapitulos;

    TemasModel *m_temas;
    LugaresModel *m_lugares;
    PersonasModel *m_personas;
    CasasModel *m_casas;

    void cargarConexiones();
    void cargarModelos();
    void cargarMenues();
};

#endif // MAINWINDOW_H
