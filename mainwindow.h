#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

class NuevoCapitulo;

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

    void cargarConexiones();
};

#endif // MAINWINDOW_H
