#ifndef DLGSELECCIONARLUGAR_H
#define DLGSELECCIONARLUGAR_H

#include <QDialog>

class LugaresModel;
class QSqlTableModel;
class ProxyNombres;

namespace Ui {
class dlgSeleccionarLugar;
}

class dlgSeleccionarLugar : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSeleccionarLugar(QWidget *parent = 0);
    ~dlgSeleccionarLugar();

private slots:

    void anadirLugar();
    void actualizarFiltro(const QString filtro);
    void aceptar();

signals:
    void lugarEscogido(Persona autor);

private:
    Ui::dlgSeleccionarLugar *ui;

    QSqlTableModel *m_lugares_base;
    ProxyNombres *m_lugares_proxy;

    // este es para añadir 
    LugaresModel *m_lugares;

    void cargarModelo();
};

#endif // DLGSELECCIONARLUGAR_H
