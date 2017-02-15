#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

class NuevoCapitulo;

class Temas;

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

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    NuevoCapitulo *Capitulo;

    Temas *m_temas;

    void cargarConexiones();
    void cargarModelos();
};

#endif // MAINWINDOW_H
