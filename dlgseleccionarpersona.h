#ifndef DLGSELECCIONARPERSONA_H
#define DLGSELECCIONARPERSONA_H

#include <QDialog>

#include "persona.h"

class PersonasModel;
class QSqlTableModel;
class ProxyNombres;

namespace Ui {
class dlgSeleccionarPersona;
}

class dlgSeleccionarPersona : public QDialog
{
    Q_OBJECT

public:
    explicit dlgSeleccionarPersona(QWidget *parent = 0);
    ~dlgSeleccionarPersona();

private slots:

    void anadirPersona();
    void actualizarFiltro(const QString filtro);
    void aceptar();

signals:
    void personaEscogida(Persona autor);

private:
    Ui::dlgSeleccionarPersona *ui;

    QSqlTableModel *m_nombres;
    ProxyNombres *m_nombres_proxy;

    PersonasModel *m_personas;

    void cargarModelo();
};

#endif // DLGSELECCIONARPERSONA_H
