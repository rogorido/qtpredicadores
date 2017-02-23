#ifndef DLGSELECCIONARPERSONA_H
#define DLGSELECCIONARPERSONA_H

#include <QDialog>

class PersonasModel;
class QSqlTableModel;
class QSortFilterProxyModel;

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

private:
    Ui::dlgSeleccionarPersona *ui;

    QSqlTableModel *m_nombres;
    QSortFilterProxyModel *m_nombres_proxy;

    PersonasModel *m_personas;

    void cargarModelo();
};

#endif // DLGSELECCIONARPERSONA_H
