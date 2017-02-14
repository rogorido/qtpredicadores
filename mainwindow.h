#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

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

    void cargarConexiones();
};

#endif // MAINWINDOW_H
