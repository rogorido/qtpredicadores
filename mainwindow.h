#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

class NuevoCapitulo;
class NuevaResolucion;
class NuevaPersona;

class TemasModel;
class Lugares;
class Personas;
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

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    NuevoCapitulo *Capitulo;
    NuevaResolucion *Resolucion;
    NuevaPersona *Persona;

    TemasModel *m_temas;
    Lugares *m_lugares;
    Personas *m_personas;
    CasasModel *m_casas;

    void cargarConexiones();
    void cargarModelos();
};

#endif // MAINWINDOW_H
