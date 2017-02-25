#ifndef DLGSELECCIONARCASA_H
#define DLGSELECCIONARCASA_H

#include <QDialog>

#include "objs/casa.h"

class CasasModel;
class QSqlTableModel;
class ProxyNombres;

namespace Ui {
class dlgSeleccionarCasa;
}

class dlgSeleccionarCasa : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSeleccionarCasa(QWidget *parent = 0);
    ~dlgSeleccionarCasa();

private slots:

    void anadirCasa();
    void actualizarFiltro(const QString filtro);
    void aceptar();

signals:
    void casaEscogida(Casa casa);

private:
    Ui::dlgSeleccionarCasa *ui;

    QSqlTableModel *m_nombres;
    ProxyNombres *m_nombres_proxy;

    CasasModel *m_casas;

    void cargarModelo();
};

#endif // DLGSELECCIONARCASA_H
